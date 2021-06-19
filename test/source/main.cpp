#include <natural.h>
using namespace natural;

class TestApp : public ApplicationListener {
	std::unique_ptr<RenderPass> m_pass;
	std::unique_ptr<Pipeline> m_pip;
public:
	void Start() {
		AttachmentDesc at;
		at.Format = GetSwapChainImageFormat();
		at.LoadOp = AttachmentLoadOp::Clear;
		at.StoreOp = AttachmentStoreOp::Store;
		at.StencilLoadOp = AttachmentLoadOp::DontCare;
		at.StencilStoreOp = AttachmentStoreOp::DontCare;
		at.InitialLayout = ImageLayout::Undefined;
		at.FinalLayout = ImageLayout::PresentSrcKhr;
		std::vector<ColorAttachmentRef> refs = { {0, ImageLayout::ColorAttachmentOptimal} };
		m_pass.reset(CreateRenderPass({ at }, { {PipelineBindPoint::Graphics, refs} }));
		m_pip.reset(CreatePipeline(GetResource<Shader>("triangle"), m_pass.get(), 0));
	}
	void Update() {
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