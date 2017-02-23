#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>

#include "VDeleter.hpp"

template <typename T>
class vDeleter;

class HelloTriangleApplication
{
public:
	void run()
	{
		initWindow();
		initVulkan();
		mainLoop();
	}
private:
	VDeleter<VkInstance> instance {vkDestroyInstance};
	GLFWwindow* window;

	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

/*
	function to create a Vulkan instance
 */
	void createInstance()
	{
		/*
		 Structure storing information about our application
		 optional but good for driver optimization
         */
		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Hello Triangle";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		/*
		 required information on global extensions and validation layers
         we intend to use
		 */
		VkInstanceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;
		/*
		 These extensions are needed to interface with the window system
		 This is profided by glfw
		 */
		unsigned int glfwExtensionCount = 0;
		const char** glfwExtensions;

		// Return the extensions needed to interface with window system
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;

		// Determine the global validation layer to enable
		createInfo.enabledLayerCount = 0;

	    /*
          Create an instance
		  provide creation information, a null pointer for custom allocator callbacks, and poiter to variable that stores the handle to the new object
		  That is we are asking Vulkan to make an instance with information contained in createInfo and place it into instance
         */
		VkResult result = vkCreateInstance(&createInfo, nullptr, instance.replace());
		if (result != VK_SUCCESS) {
			throw std::runtime_error("failed to create instance!");
		}
	}

	void initWindow()
	{
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Vulkan", nullptr, nullptr);
	}

	void initVulkan()
	{
		createInstance();
	}

	void mainLoop()
	{
		while (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();
		}

		glfwDestroyWindow(window);
	}
};

int main(int argc, char** argv)
{
	HelloTriangleApplication app;

	try
	{
		app.run();
	} catch (const std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
