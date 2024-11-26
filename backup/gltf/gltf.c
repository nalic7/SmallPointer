//need math to use this
//use index to create triangle
#define CGLTF_IMPLEMENTATION
#include <cgltf.h>

// // int check()
// // {
// //	 VkResult result;

// //	 // Initialize Vulkan
// //	 VkInstance instance;
// //	 VkApplicationInfo appInfo = {
// //		 .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
// //		 .pNext = NULL,
// //		 .pApplicationName = "Vulkan Check",
// //		 .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
// //		 .pEngineName = "No Engine",
// //		 .engineVersion = VK_MAKE_VERSION(1, 0, 0),
// //		 .apiVersion = VK_API_VERSION_1_2
// //	 };

// //	 VkInstanceCreateInfo createInfo = {
// //		 .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
// //		 .pNext = NULL,
// //		 .flags = 0,
// //		 .pApplicationInfo = &appInfo,
// //		 .enabledLayerCount = 0,
// //		 .ppEnabledLayerNames = NULL,
// //		 .enabledExtensionCount = 0,
// //		 .ppEnabledExtensionNames = NULL
// //	 };

// //	 result = vkCreateInstance(&createInfo, NULL, &instance);
// //	 if (result != VK_SUCCESS) {
// //		 info("Failed to create Vulkan instance: %d", result)
// //		 return EXIT_FAILURE;
// //	 }

// //	 info("Vulkan instance created successfully.")

// //	 // Enumerate physical devices
// //	 uint32_t deviceCount = 0;
// //	 vkEnumeratePhysicalDevices(instance, &deviceCount, NULL);
// //	 if (deviceCount == 0) {
// //		 info("No Vulkan-compatible physical devices found.")
// //		 vkDestroyInstance(instance, NULL);
// //		 return EXIT_FAILURE;
// //	 }

// //	 VkPhysicalDevice *physicalDevices = malloc(sizeof(VkPhysicalDevice) * deviceCount);
// //	 if (physicalDevices == NULL) {
// //		 info("Failed to allocate memory for physical devices.")
// //		 vkDestroyInstance(instance, NULL);
// //		 return EXIT_FAILURE;
// //	 }

// //	 vkEnumeratePhysicalDevices(instance, &deviceCount, physicalDevices);
// //	 info("Found %d Vulkan-compatible physical devices.", deviceCount)

// //	 // Select the first physical device
// //	 VkPhysicalDevice physicalDevice = physicalDevices[0];
// //	 free(physicalDevices);

// //	 // Create a logical device
// //	 VkDevice device;
// //	 VkDeviceCreateInfo deviceCreateInfo = {
// //		 .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
// //		 .pNext = NULL,
// //		 .flags = 0,
// //		 .queueCreateInfoCount = 0,
// //		 .pQueueCreateInfos = NULL,
// //		 .enabledLayerCount = 0,
// //		 .ppEnabledLayerNames = NULL,
// //		 .enabledExtensionCount = 0,
// //		 .ppEnabledExtensionNames = NULL,
// //		 .pEnabledFeatures = NULL
// //	 };

// //	 result = vkCreateDevice(physicalDevice, &deviceCreateInfo, NULL, &device);
// //	 if (result != VK_SUCCESS) {
// //		 info("Failed to create Vulkan device: %d", result)
// //		 vkDestroyInstance(instance, NULL);
// //		 return EXIT_FAILURE;
// //	 }

// //	 info("Vulkan device created successfully.")

// //	 // Cleanup
// //	 vkDestroyDevice(device, NULL);
// //	 vkDestroyInstance(instance, NULL);
// //	 return EXIT_FAILURE;
// // }

// // // int main()
// // // {
// // //	 info("Hello, CMake!")
// // //	 return 0;
// // // }

// // int thread_function(void *arg)
// // {
// //	 while (1)
// //	 {
// //		 info("Hello from the thread!")

// //		 // Sleep for 1 second
// //		 struct timespec ts = {1, 0}; // 1 second
// //		 thrd_sleep(&ts, NULL);
// //	 }
// //	 return 0;
// // }

// JNIEXPORT void JNICALL Java_com_nali_summer_SmallRender_runtime(JNIEnv *env, jobject obj)
// {
//	 // info("Hello, CMake! %d", check())

//	 // thrd_t thread;
//	 // int result = thrd_create(&thread, thread_function, NULL);
//	 // if (result != thrd_success)
//	 // {
//	 //	 info("Error creating thread")
//	 //	 return;
//	 // }

//	 // // thrd_join(thread, NULL);
//	 // info("Hello from the main thread!")
// }

static size_t thrd;

void main_write_file(const char *path, const void *data, size_t size, size_t n_size)
{
	FILE *file = fopen(path, "wb");
	if (!file)
	{
		error("fopen")
	}

	if (fwrite(data, size, n_size, file) != n_size)
	{
		error("fwrite");
	}

	fclose(file);
}

int main_skin_gltf(void *name)
{
	cgltf_options cgltf_options = {0};
	cgltf_data *cgltf_data;
	char *n0 = math_combine(GLTF_IN, "/");
	char *n_in = math_combine(n0, name);
	free(n0);
	n0 = math_combine(GLTF_OUT, "/");

	cgltf_result result = cgltf_parse_file(&cgltf_options,  n_in, &cgltf_data);
	if (result == cgltf_result_success)
	{
		if (cgltf_load_buffers(&cgltf_options, cgltf_data, n_in))
		{
			error("cgltf_load_buffers")
		}

		char *dot_ptr = strchr(name, '.');

		if (dot_ptr)
		{
			*dot_ptr = '\0';
		}

		char *n_out = math_combine(n0, name);
		free(n0);

		for (size_t i = 0; i < cgltf_data->meshes_count; ++i)
		{
			cgltf_mesh cgltf_mesh = cgltf_data->meshes[i];
			char *n2 = math_combine(n_out, cgltf_mesh.name);
			mkdir(n2, 0700);
			char *n_mesh = math_combine(n2, "/");
			free(n2);

			for (size_t l = 0; l < cgltf_mesh.primitives_count; ++l)
			{
				cgltf_primitive cgltf_primitive = cgltf_mesh.primitives[l];
				for (size_t j = 0; j < cgltf_primitive.attributes_count; ++j)
				{
					cgltf_attribute cgltf_attribute = cgltf_primitive.attributes[j];
					n2 = math_combine(n_mesh, cgltf_attribute.name);
					n0 = math_combine(n2, ".bin");
					free(n2);

					cgltf_accessor *cgltf_accessor_ptr = cgltf_attribute.data;
					cgltf_size cgltf_size_count = cgltf_accessor_ptr->count;
					cgltf_size cgltf_size_type = cgltf_num_components(cgltf_accessor_ptr->type);
					void *a_data;
					// size_t a_size = cgltf_size_count * cgltf_size_type;
					switch (cgltf_accessor_ptr->component_type)
					{
						case cgltf_component_type_r_32f:
							a_data = malloc(cgltf_size_count * sizeof(cgltf_float));
							// // a_size /= sizeof(cgltf_float);
							// // cgltf_float *cgltf_float = a_data;
							// for (size_t k = 0; k < cgltf_size_count; ++k)
							// {
							// 	cgltf_accessor_read_float(cgltf_accessor_ptr, k, &a_data[k * cgltf_size_type], cgltf_size_type);
							// 	// if (cgltf_size_type == 4)
							// 	// {
							// 	// 	info("wx%f, wy%f wz%f ww%f", cgltf_float[k], cgltf_float[k + 1], cgltf_float[k + 2], cgltf_float[k + 3])
							// 	// }
							// }
							break;
						case cgltf_component_type_r_8u:
							a_data = malloc(cgltf_size_count * sizeof(cgltf_uint));
							// // a_size /= sizeof(cgltf_uint);
							// // cgltf_uint *cgltf_uint = a_data;
							// for (size_t k = 0; k < cgltf_size_count; ++k)
							// {
							// 	//find max joints with weight
							// 	cgltf_accessor_read_uint(cgltf_accessor_ptr, k, &a_data[k * cgltf_size_type], cgltf_size_type);
							// 	// info("jx%d, jy%d jz%d jw%d", cgltf_uint[k], cgltf_uint[k + 1], cgltf_uint[k + 2], cgltf_uint[k + 3])
							// }
							break;
						default:
							error("cgltf_accessor_ptr->type")
					}

					// if (strcmp(cgltf_attribute.name, "JOINTS_0") == 0 || strcmp(cgltf_attribute.name, "WEIGHTS_0") == 0)
					// {
					// 	// a_size = cgltf_size_count * max_joint;
					// 	a_size = cgltf_size_count * 4;
					// }
					info("%s %ld / %ld", n0, cgltf_accessor_ptr->stride, cgltf_size_type)
					main_write_file(n0, a_data, cgltf_accessor_ptr->stride / cgltf_size_type, cgltf_size_count);
					free(n0);
					free(a_data);
				}

				n2 = math_combine(n_mesh, "index.bin");

				cgltf_accessor *cgltf_accessor_ptr = cgltf_primitive.indices;
				cgltf_size cgltf_size_count = cgltf_accessor_ptr->count;
				FILE *file = fopen(n2, "wb");
				if (!file)
				{
					error("fopen")
				}

				info("%s %ld / 1", n2, cgltf_accessor_ptr->stride)
				cgltf_size cgltf_size_type = cgltf_num_components(cgltf_accessor_ptr->type);
				for (size_t j = 0; j < cgltf_size_count; ++j)
				{
					cgltf_size cgltf_size = cgltf_accessor_read_index(cgltf_accessor_ptr, j);
					fwrite(&cgltf_size, cgltf_accessor_ptr->stride / cgltf_size_type, 1, file);
					// fwrite(&cgltf_size, sizeof(uint32_t), 1, file);
				}

				fclose(file);
				free(n2);
			}

			free(n_mesh);
		}

		char *n_ani = math_combine(n_out, "/");
		mkdir(n_out, 0700);
		free(n_out);

		for (size_t i = 0; i < cgltf_data->skins_count; ++i)
		{
			const cgltf_skin *skin = &cgltf_data->skins[i];

			if (skin->inverse_bind_matrices != NULL)
			{
				n0 = math_combine(n_ani, "bindpose.bin");

				cgltf_accessor *cgltf_accessor_ptr = skin->inverse_bind_matrices;
				cgltf_size cgltf_size_count = cgltf_accessor_ptr->count;
				cgltf_size cgltf_size_type = cgltf_num_components(cgltf_accessor_ptr->type);
				void *a_data;
				// size_t a_size = cgltf_size_count * cgltf_size_type;
				switch (cgltf_accessor_ptr->component_type)
				{
					case cgltf_component_type_r_32f:
						a_data = malloc(cgltf_size_count * sizeof(cgltf_float));
						// a_size /= sizeof(cgltf_float);
						// cgltf_float *cgltf_float = a_data;
						for (size_t k = 0; k < cgltf_size_count; ++k)
						{
							cgltf_accessor_read_float(cgltf_accessor_ptr, k, &a_data[k * cgltf_size_type], cgltf_size_type);
						}
						break;
					default:
						error("cgltf_accessor_ptr->type")
				}
				info("%s %ld / %ld", n0, cgltf_accessor_ptr->stride, cgltf_size_type)
				main_write_file(n0, a_data, cgltf_accessor_ptr->stride / cgltf_size_type, cgltf_size_count);
				free(n0);
				free(a_data);
			}
		}

		// char max_joint = 0;
		for (size_t i = 0; i < cgltf_data->nodes_count; ++i)
		{
			const cgltf_node *node = &cgltf_data->nodes[i];
			// if (max_joint < node->weights_count)
			// {
			// 	max_joint = node->weights_count;
			// }

			if (node->name)
			{
				printf("Bone Name: %s\n", node->name);
			}
			else
			{
				printf("Bone Name: (unnamed)\n");
			}

			if (node->has_matrix)
			{
				printf("Transformation Matrix:\n");
				for (int j = 0; j < 16; ++j)
				{
					printf("%f ", node->matrix[j]);
					if ((j + 1) % 4 == 0)
					{
						printf("\n");
					}
				}
			}
			else
			{
				printf("Translation: (%f, %f, %f)\n", node->translation[0], node->translation[1], node->translation[2]);
				printf("Rotation: (%f, %f, %f, %f)\n", node->rotation[0], node->rotation[1], node->rotation[2], node->rotation[3]);
				printf("Scale: (%f, %f, %f)\n", node->scale[0], node->scale[1], node->scale[2]);
			}

			for (size_t j = 0; j < node->children_count; ++j)
			{
				printf(" - Child Index: %zu\n", node->children[j] - cgltf_data->nodes); // Assuming you want the index in the node array
			}
			printf("\n");
		}

		for (size_t i = 0; i < cgltf_data->animations_count; ++i) {
			const cgltf_animation *animation = &cgltf_data->animations[i];
			printf("Animation Name: %s\n", animation->name ? animation->name : "(unnamed)");

			// Iterate over animation channels
			for (size_t j = 0; j < animation->channels_count; ++j) {
				const cgltf_animation_channel *channel = &animation->channels[j];
				printf("Channel %zu:\n", j);

				// Print target node
				printf(" Target Node Index: %zu\n", channel->target_node - cgltf_data->nodes);

				// Print target path
				printf(" Target Path: %d\n", channel->target_path);

				// Print sampler information
				const cgltf_animation_sampler *sampler = animation->samplers;

				// Print keyframe times
				const cgltf_accessor *time_accessor = sampler->input;
				const float *times = (const float *)time_accessor->buffer_view->buffer->data;
				size_t time_count = time_accessor->count;
				printf(" Keyframe Times:\n");
				for (size_t k = 0; k < time_count; ++k) {
					printf("  Time %zu: %f\n", k, times[k]);
				}

				// Print keyframe values
				const cgltf_accessor *value_accessor = sampler->output;
				const float *values = (const float *)value_accessor->buffer_view->buffer->data;
				size_t value_count = value_accessor->count;
				printf(" Keyframe Values:\n");
				for (size_t k = 0; k < value_count; ++k) {
					printf("  Value %zu: %f\n", k, values[k]);
				}
			}
			printf("\n");
		}

		free(n_ani);

	}
	else
	{
		error("cgltf_parse_file")
	}

	cgltf_free(cgltf_data);
	free(n_in);
	free(name);
	--thrd;
	return 0;
}

int main()
{
	mkdir(GLTF_IN, 0700);
	mkdir(GLTF_OUT, 0700);

	DIR *dir = opendir(GLTF_IN);
	if (!dir)
	{
		error("opendir")
	}

	struct dirent *dirent_ptr;
	while ((dirent_ptr = readdir(dir)) != NULL)
	{
		const char *d_name = dirent_ptr->d_name;
		size_t size = strlen(d_name) + 1;
		char *name = malloc(size);
		memcpy(name, d_name, size);
		struct stat _stat;

		char *n0 = math_combine(GLTF_IN, "/");
		char *n1 = math_combine(n0, name);
		free(n0);

		if (stat(n1, &_stat))
		{
			error("stat")
		}

		if (S_ISREG(_stat.st_mode))//S_ISDIR
		{
			thrd_t thread;

			if (thrd_create(&thread, main_skin_gltf, name) != thrd_success)
			{
				error("thrd_create")
			}

			++thrd;
		}

		free(n1);
	}

	closedir(dir);

	while (thrd){}
}

// int main()
// {
//	 cgltf_options cgltf_options = {0};
//	 cgltf_data *cgltf_data;

//	 cgltf_result result = cgltf_parse_file(&cgltf_options,  GLTF_IN "/Ibuki.glb", &cgltf_data);
	
//	 if (result == cgltf_result_success)
//	 {
//		 result = cgltf_load_buffers(&cgltf_options, cgltf_data, GLTF_IN "/Ibuki.glb");

//		 if (result == cgltf_result_success)
//		 {
//			 cgltf_size cgltf_size_count = cgltf_data->meshes->primitives->attributes->data->count;
//			 cgltf_size cgltf_size_type = cgltf_num_components(cgltf_data->meshes->primitives->attributes->data->type);
//			 size_t f_size = cgltf_size_count * cgltf_size_type * sizeof(float);
//			 float f_ptr[cgltf_size_count * cgltf_size_type];
//			 for (size_t k = 0; k < cgltf_size_count; ++k)
//			 {
//				 cgltf_accessor_read_float(cgltf_data->meshes->primitives->attributes->data, k, f_ptr, cgltf_size_type);
//			 }
//			 char t = 't';
//		 }
//	 }
// }
