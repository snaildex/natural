#include <natural.h>
using namespace natural;

class TestApp : public ApplicationListener {
	const int MaxFramesInFlight = 2;
	std::unique_ptr<RenderPass> m_pass;
	std::unique_ptr<Pipeline> m_pip;
	std::vector<std::unique_ptr<Framebuffer>> m_fbufs;
	std::unique_ptr<CommandPool> m_comPool;
	std::vector<std::unique_ptr<CommandBuffer>> m_comBufs;
	std::vector<std::unique_ptr<Semaphore>> m_imageAvailable;
	std::vector<std::unique_ptr<Semaphore>> m_renderFinished;
	std::vector<std::unique_ptr<Fence>> m_inFlightFences;
	std::vector<Fence*> m_imagesInFlight;
	int m_currentFrame;

	void Init() {
		for (int i = 0; i < m_comBufs.size(); ++i) m_comBufs[i].reset();
		AttachmentDesc at;
		at.Format = GetSwapChainImageFormat();
		at.LoadOp = AttachmentLoadOp::Clear;
		at.StoreOp = AttachmentStoreOp::Store;
		at.StencilLoadOp = AttachmentLoadOp::DontCare;
		at.StencilStoreOp = AttachmentStoreOp::DontCare;
		at.InitialLayout = ImageLayout::Undefined;
		at.FinalLayout = ImageLayout::PresentSrcKhr;
		std::vector<ColorAttachmentRef> refs = { {0, ImageLayout::ColorAttachmentOptimal} };
		std::unique_ptr<RenderPassBuilder> rpBuilder;
		BuildRenderPass(rpBuilder);
		rpBuilder->AddAttachment(at);
		rpBuilder->AddSubpass({ PipelineBindPoint::Graphics, refs });
		SubpassDependencyDesc dep;
		dep.SrcSubpass = SubpassExternal;
		dep.DstSubpass = 0;
		dep.SrcStageMask = PipelineStage::ColorAttachmentOutput;
		dep.SrcAccessMask = 0;
		dep.DstStageMask = PipelineStage::ColorAttachmentOutput;
		dep.DstAccessMask = Access::ColorAttachmentWrite;
		dep.DependencyFlags = 0;
		rpBuilder->AddSubpassDependency(dep);
		rpBuilder->Build(m_pass);
		CreatePipeline(m_pip, GetResource<Shader>("triangle"), m_pass.get(), 0);
		CreateSwapchainFramebuffers(m_fbufs, m_pass.get());
		CreateCommandPool(m_comPool);
		m_imageAvailable.resize(MaxFramesInFlight);
		m_renderFinished.resize(MaxFramesInFlight);
		m_inFlightFences.resize(MaxFramesInFlight);
		for (int i = 0; i < MaxFramesInFlight; ++i) {
			CreateSemaphore(m_imageAvailable[i]);
			CreateSemaphore(m_renderFinished[i]);
			CreateFence(m_inFlightFences[i], true);
		}
		m_imagesInFlight.resize(m_fbufs.size());
		std::fill(m_imagesInFlight.begin(), m_imagesInFlight.end(), nullptr);
		m_comBufs.resize(m_fbufs.size());
		glm::uvec2 resolution = GetSwapChainExtent();
		for (int i = 0; i < m_comBufs.size(); ++i) {
			m_comPool->CreatePrimaryBuffer(m_comBufs[i]);
			CommandBuffer* comBuf = m_comBufs[i].get();
			comBuf->Begin();
			comBuf->CmdBeginRenderPass(
				m_pass.get(),
				m_fbufs[i].get(),
				{ 0,0 },
				{ resolution.x,resolution.y },
				{ {0.0f,0.0f,0.0f,1.0f} });
			comBuf->CmdBindPipeline(m_pip.get(), PipelineBindPoint::Graphics);
			comBuf->CmdDraw(3, 1, 0, 0);
			comBuf->CmdEndRenderPass();
			comBuf->End();
		}
	}

public:
	void Start() override {
		Init();
		m_currentFrame = 0;
	}
	void FramebufferResized() override {
		Init();
	}
	void Update() override {
		Wait({ m_inFlightFences[m_currentFrame].get() });
		uint32_t img = NextSwapChainImage(m_imageAvailable[m_currentFrame].get(), nullptr);
		if (m_imagesInFlight[img]) Wait({ m_imagesInFlight[img] });
		m_imagesInFlight[img] = m_inFlightFences[m_currentFrame].get();
		m_inFlightFences[m_currentFrame]->Reset();
		SubmitQueue(
			{ {m_imageAvailable[m_currentFrame].get(), PipelineStage::ColorAttachmentOutput} },
			{ m_comBufs[img].get() },
			{ m_renderFinished[m_currentFrame].get() },
			m_inFlightFences[m_currentFrame].get()
		);
		Present({ m_renderFinished[m_currentFrame].get() }, img);
		m_currentFrame = (m_currentFrame + 1) % MaxFramesInFlight;
	}
};

int main(int argc, char* argv[]) {
	std::unique_ptr<Application> app(Application::Create(800, 600, "Kek", new TestApp()));
	try {
		app->Run();
	}
	catch (const std::exception& e) {
		Log("application error:\n%s", e.what());
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}