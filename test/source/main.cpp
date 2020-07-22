#include <natural.h>
using namespace natural;

class TestApp : public ApplicationListener {
	Pipeline* m_pip;
	std::unique_ptr<RenderPass> m_pass;
public:
	void Start() {
		m_pip = Application()->GetResource<Pipeline>("triangle");
		m_pip->StartLoading();
		m_pass.reset(Application()->CreateRenderPass());
	}
	void Update() {

	}
};


int main(int argc, char* argv[]) {
	std::unique_ptr<Application> app(Application::Create(800, 600, "Kek", new TestApp()));
	try {
		app->Run();
	}
	catch (const std::exception & e) {
		Log("application error:\n%s", e.what());
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}