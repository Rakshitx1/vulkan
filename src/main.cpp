#include <iostream>
#include <vector> 
#include <vulkan/vulkan.hpp>

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
    std::cout << "Vulkan initialization successful." << std::endl;

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

    // Enumerate physical devices
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    if (deviceCount == 0) {
        std::cerr << "Failed to find GPUs with Vulkan support." << std::endl;
        vkDestroyInstance(instance, nullptr);
        return false;
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    std::cout << deviceCount << " Vulkan physical device(s) found." << std::endl;

    for (const auto& device : devices) {
        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);

        std::cout << "Device Name: " << deviceProperties.deviceName << std::endl;
        std::cout << "Device Type: ";
        switch (deviceProperties.deviceType) {
            case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
                std::cout << "Integrated GPU" << std::endl;
                break;
            case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
                std::cout << "Discrete GPU" << std::endl;
                break;
            case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
                std::cout << "Virtual GPU" << std::endl;
                break;
            case VK_PHYSICAL_DEVICE_TYPE_CPU:
                std::cout << "CPU" << std::endl;
                break;
            default:
                std::cout << "Unknown" << std::endl;
                break;
        }

        std::cout << "API Version: " << VK_VERSION_MAJOR(deviceProperties.apiVersion) << "."
                  << VK_VERSION_MINOR(deviceProperties.apiVersion) << "."
                  << VK_VERSION_PATCH(deviceProperties.apiVersion) << std::endl;
    }

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
