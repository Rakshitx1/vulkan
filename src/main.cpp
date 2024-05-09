#include <iostream>
#include <vulkan/vulkan.h>

bool vulkanCheck() {
    // Vulkan instance creation
    VkInstance instance;
    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
    if (result != VK_SUCCESS) {
        std::cerr << "Vulkan initialization failed: Error code " << result << std::endl;
        return false;
    }
    else {
        std::cout << "Vulkan initialization successful." << std::endl;
    }

    // Enumerate Vulkan extensions
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::cout << extensionCount << " Vulkan extensions supported." << std::endl;

    // Query Vulkan version
    uint32_t apiVersion = 0;
    vkEnumerateInstanceVersion(&apiVersion);
    std::cout << "Vulkan API version: " << VK_VERSION_MAJOR(apiVersion) << "."
              << VK_VERSION_MINOR(apiVersion) << "."
              << VK_VERSION_PATCH(apiVersion) << std::endl;

    // Cleanup
    vkDestroyInstance(instance, nullptr);

    return true;
}

int main() {
    if (!vulkanCheck()) {
        return 1;
    }

    return 0;
}
