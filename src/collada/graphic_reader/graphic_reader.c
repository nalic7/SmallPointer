// void graphic_reader_repaste(char *char_ptr, char c_char, char r_char)
// {
// 	while (*char_ptr)
// 	{
// 		if (*char_ptr == c_char)
// 		{
// 			*char_ptr = r_char;
// 		}
// 		++char_ptr;
// 	}
// }

uint32_t graphic_reader_count(char *char_ptr, char c_char)
{
	uint32_t v = 0;

	while (*char_ptr)
	{
		if (*char_ptr == c_char)
		{
			++v;
		}
		++char_ptr;
	}

	return v;
}

void graphic_reader_sanitize(char *char_ptr)
{
	while (*char_ptr)
	{
		if (!isalnum(*char_ptr))
		{
			*char_ptr = '_';
		}
		++char_ptr;
	}
}

// void graphic_reader_switchBones(SourceDataType *sourcedatatype_ptr)
// {
// 	sourcedatatype_ptr->visual_bones_bonedata_vector_vector = malloc(sourcedatatype_ptr->max_object * sizeof(BoneData *));

// 	for (int z = 0; z < sourcedatatype_ptr->max_object; ++z)
// 	{
// 		sourcedatatype_ptr->visual_bones_bonedata_vector_vector[z] = malloc(sourcedatatype_ptr->joints_size[z] * sizeof(BoneData));
// 		sourcedatatype_ptr->visual_bones_bonedata_vector_vector[z] = malloc(0);
// 	}

// 	for (int x = 0; x < sourcedatatype_ptr->max_animation_bones; ++x)
// 	{
// 		BoneData bonedata = sourcedatatype_ptr->bonedata_vector[x];

// 		for (int y = 0; y < bonedata.bones_name_string_size; y += 2)
// 		{
// 			uint32_t index = 0;
// 			for (int z = 0; z < sourcedatatype_ptr->max_object; ++z)
// 			{
// 				for (int w = 0; w < sourcedatatype_ptr->joints_size[z]; ++w)
// 				{
// 					if (strcmp(sourcedatatype_ptr->joints[z][w], bonedata.bones_name_string[y]) == 0)
// 					{
// 						sourcedatatype_ptr->visual_bones_bonedata_vector_vector[z] = realloc(sourcedatatype_ptr->visual_bones_bonedata_vector_vector[z], sizeof(BoneData));
// 						BoneData visual_bones_bonedata = sourcedatatype_ptr->visual_bones_bonedata_vector_vector[z][w];
// 						visual_bones_bonedata.bones_name_string[index] = sourcedatatype_ptr->joints[z][w];
// 						visual_bones_bonedata.space_int = bonedata.space_int;
// 						visual_bones_bonedata.visual_bones_transform_float_vector = bonedata.visual_bones_transform_float_vector;
// 					}
// 				}
// 			}
// 		}
// 	}
// }

// void graphic_reader_switchAnimationBones(SourceDataType *sourcedatatype_ptr)
// {
// 	for (int y = 0; y < sourcedatatype_ptr->joints.size(); ++y)
// 	{
// 		for (int z = 0; z < sourcedatatype_ptr->joints[y].size(); ++z)
// 		{
// 			int index = GraphicReader::matchString(sourcedatatype_ptr->joints[y][z], sourcedatatype_ptr->armature_string_vector, '*', '*');
// 			if (index != -1)
// 			{
// 				sourcedatatype_ptr->armature_string_vector[index] = sourcedatatype_ptr->joints[y][z];
// 			}
// 		}
// 	}
// }

void graphic_reader_makeBones(SourceDataType *sourcedatatype_ptr)
{
	BoneData *bonedata_vector = sourcedatatype_ptr->bonedata_vector;
	sourcedatatype_ptr->max_bones_string_vector_vector_vector = malloc(sizeof(uint32_t *) * sourcedatatype_ptr->max_object);
	sourcedatatype_ptr->bones_string_vector_vector_vector = malloc(sizeof(char ***) * sourcedatatype_ptr->max_object);

	for (int x = 0; x < sourcedatatype_ptr->max_object; ++x)
	{
		sourcedatatype_ptr->max_bones_string_vector_vector_vector[x] = malloc(sizeof(uint32_t) * sourcedatatype_ptr->joints_size[x]);
		sourcedatatype_ptr->bones_string_vector_vector_vector[x] = malloc(sizeof(char **) * sourcedatatype_ptr->joints_size[x]);

		for (int w = 0; w < sourcedatatype_ptr->joints_size[x]; ++w)
		{
			for (int y = 0; y < sourcedatatype_ptr->max_bonedata; ++y)
			{
				if (strcmp(sourcedatatype_ptr->joints[x][w], bonedata_vector[y].bones_name_string[0]) == 0)
				{
					char** char_ptr = malloc(sizeof(char *));
					// uint32_t max_z = sourcedatatype_ptr->space_ptr[y / 2];
					uint32_t max_z = sourcedatatype_ptr->space_ptr[w];
					uint32_t index = 0;
					char_ptr[index++] = bonedata_vector[y].bones_name_string[0];

					for (int z = y - 1; z - 1 > -2; --z)
					{
						uint32_t new_max_z = sourcedatatype_ptr->space_ptr[z];
						if (max_z > new_max_z)
						{
							max_z = new_max_z;
							char_ptr = realloc(char_ptr, sizeof(char *) * (index + 1));
							char_ptr[index++] = bonedata_vector[z].bones_name_string[0];
						}
					}

					sourcedatatype_ptr->max_bones_string_vector_vector_vector[x][w] = index;
					sourcedatatype_ptr->bones_string_vector_vector_vector[x][w] = char_ptr;
					break;
				}
			}
		}
	}
}

void graphic_reader_compressVertex(SourceDataType *sourcedatatype_ptr)
{
	size_t fs_size = sizeof(float *) * sourcedatatype_ptr->max_object;
	size_t uis_size = sizeof(uint32_t *) * sourcedatatype_ptr->max_object;
	sourcedatatype_ptr->indexdata.positions = malloc(fs_size);
	sourcedatatype_ptr->indexdata.normals = malloc(fs_size);
	sourcedatatype_ptr->indexdata.texcoord = malloc(fs_size);

	for (int x = 0; x < sourcedatatype_ptr->max_object; ++x)
	{
		uint32_t p_offset_size = sourcedatatype_ptr->p_offset_size[x];
		size_t f_size = sizeof(float) * p_offset_size;
		sourcedatatype_ptr->indexdata.positions[x] = malloc(f_size);
		sourcedatatype_ptr->indexdata.normals[x] = malloc(f_size);
		sourcedatatype_ptr->indexdata.texcoord[x] = malloc(f_size);

		for (int y = 0; y < p_offset_size; ++y)
		{
			int xv = sourcedatatype_ptr->positions_offset[x][y] * 3;
			int yv = sourcedatatype_ptr->positions_offset[x][y] * 3 + 1;
			int zv = sourcedatatype_ptr->positions_offset[x][y] * 3 + 2;
			int xn = sourcedatatype_ptr->normals_offset[x][y] * 3;
			int yn = sourcedatatype_ptr->normals_offset[x][y] * 3 + 1;
			int zn = sourcedatatype_ptr->normals_offset[x][y] * 3 + 2;
			int ut = sourcedatatype_ptr->texcoord_offset[x][y] * 2;
			int vt = sourcedatatype_ptr->texcoord_offset[x][y] * 2 + 1;

			sourcedatatype_ptr->indexdata.positions[x][y * 3] = sourcedatatype_ptr->positions[x][xv];
			sourcedatatype_ptr->indexdata.positions[x][y * 3 + 1] = sourcedatatype_ptr->positions[x][yv];
			sourcedatatype_ptr->indexdata.positions[x][y * 3 + 2] = sourcedatatype_ptr->positions[x][zv];
			sourcedatatype_ptr->indexdata.normals[x][y * 3] = sourcedatatype_ptr->normals[x][xn];
			sourcedatatype_ptr->indexdata.normals[x][y * 3 + 1] = sourcedatatype_ptr->normals[x][yn];
			sourcedatatype_ptr->indexdata.normals[x][y * 3 + 1] = sourcedatatype_ptr->normals[x][zn];
			sourcedatatype_ptr->indexdata.texcoord[x][y * 2] = sourcedatatype_ptr->texcoord[x][ut];
			sourcedatatype_ptr->indexdata.texcoord[x][y * 2 + 1] = sourcedatatype_ptr->texcoord[x][vt];
		}
	}

	if (sourcedatatype_ptr->create_animation)
	{
		sourcedatatype_ptr->indexdata.joints = malloc(uis_size);
		sourcedatatype_ptr->indexdata.weights = malloc(fs_size);

		sourcedatatype_ptr->pack_joints_size = malloc(sizeof(uint32_t) * sourcedatatype_ptr->max_object);
		sourcedatatype_ptr->pack_weights_size = malloc(sizeof(uint32_t) * sourcedatatype_ptr->max_object);
		sourcedatatype_ptr->pack_joints = malloc(uis_size);
		sourcedatatype_ptr->pack_weights = malloc(fs_size);

		for (int x = 0; x < sourcedatatype_ptr->max_object; ++x)
		{
			uint32_t p_offset_size = sourcedatatype_ptr->p_offset_size[x];
			size_t f_size = sizeof(float) * p_offset_size;
			uint32_t max_joint = sourcedatatype_ptr->max_joint_vector[x];
			sourcedatatype_ptr->pack_joints[x] = malloc(sizeof(uint32_t) * max_joint);
			sourcedatatype_ptr->pack_weights[x] = malloc(sizeof(float) * max_joint);

			for (int j = 0; j < max_joint; ++j)
			{
				sourcedatatype_ptr->pack_joints[x][j] = 0;
				sourcedatatype_ptr->pack_weights[x][j] = 0.0F;
			}

			for (int y = 0; y < p_offset_size; ++y)
			{
				{
					int v_offset_by_p = 0;

					for (int i = 0; i < sourcedatatype_ptr->positions_offset[x][y]; ++i)
					{
						v_offset_by_p += sourcedatatype_ptr->vcount_offset[x][i];
					}

					v_offset_by_p *= 2;

					int vc = sourcedatatype_ptr->vcount_offset[x][sourcedatatype_ptr->positions_offset[x][y]];

					int vc_in = 0;
					int vc_out = 0;
					sourcedatatype_ptr->pack_joints_size[x] = 0;

					while (vc_out < vc)
					{
						sourcedatatype_ptr->pack_joints[x][sourcedatatype_ptr->pack_joints_size[x]] = sourcedatatype_ptr->v_offset[x][v_offset_by_p + vc_in];
						++sourcedatatype_ptr->pack_joints_size[x];
						++vc_out;
						vc_in += 2;
					}
				}

				{
					int v_offset_by_p = 0;

					for (int i = 0; i < sourcedatatype_ptr->positions_offset[x][y]; ++i)
					{
						v_offset_by_p += sourcedatatype_ptr->vcount_offset[x][i];
					}

					v_offset_by_p *= 2;

					int vc = sourcedatatype_ptr->vcount_offset[x][sourcedatatype_ptr->positions_offset[x][y]];

					int vc_in = 0;
					int vc_out = 0;
					sourcedatatype_ptr->pack_weights_size[x] = 0;

					while (vc_out < vc)
					{
						sourcedatatype_ptr->pack_weights[x][sourcedatatype_ptr->pack_weights_size[x]] = sourcedatatype_ptr->weights[x][sourcedatatype_ptr->v_offset[x][v_offset_by_p + vc_in + 1]];
						++sourcedatatype_ptr->pack_weights_size[x];
						++vc_out;
						vc_in += 2;
					}
				}
			}
		}
	}

	// sourcedatatype_ptr->indexdata.positions = positions;
	// sourcedatatype_ptr->indexdata.normals = normals;
	// sourcedatatype_ptr->indexdata.texcoord = texcoord;

	// if (SourceDataType::CREATE_COLOR)
	// {
	// 	std::vector<std::vector<float>> color(sourcedatatype_ptr->positions_offset.size());
	//
	// 	for (int x = 0; x < sourcedatatype_ptr->positions_offset.size(); ++x)
	// 	{
	// 		sourcedatatype_ptr->pack_color.push_back({});
	//
	// 		for (int y = 0; y < sourcedatatype_ptr->positions_offset[x].size(); ++y)
	// 		{
	// 			int xv = sourcedatatype_ptr->color_offset[x][y] * 4;
	// 			int yv = sourcedatatype_ptr->color_offset[x][y] * 4 + 1;
	// 			int zv = sourcedatatype_ptr->color_offset[x][y] * 4 + 2;
	// 			int wv = sourcedatatype_ptr->color_offset[x][y] * 4 + 3;
	//
	// 			color[x].push_back(sourcedatatype_ptr->color[x][xv]);
	// 			color[x].push_back(sourcedatatype_ptr->color[x][yv]);
	// 			color[x].push_back(sourcedatatype_ptr->color[x][zv]);
	// 			color[x].push_back(sourcedatatype_ptr->color[x][wv]);
	// 		}
	// 	}
	//
	// 	sourcedatatype_ptr->indexdata.color = color;
	// }

	sourcedatatype_ptr->index = malloc(sizeof(uint32_t **) * sourcedatatype_ptr->max_object);

	for (int x = 0; x < sourcedatatype_ptr->max_object; ++x)
	{
		sourcedatatype_ptr->index = malloc(sizeof(uint32_t) * );

		for (int y = 0; y < sourcedatatype_ptr->positions_size[x] / 3; ++y)
		{
			if (canPackNew(sourcedatatype, x, y))
			{
				sourcedatatype_ptr->index[x].push_back({});
				sourcedatatype_ptr->pack_positions[x].push_back(positions[x][y * 3]);
				sourcedatatype_ptr->pack_positions[x].push_back(positions[x][y * 3 + 1]);
				sourcedatatype_ptr->pack_positions[x].push_back(positions[x][y * 3 + 2]);
				sourcedatatype_ptr->pack_normals[x].push_back(normals[x][y * 3]);
				sourcedatatype_ptr->pack_normals[x].push_back(normals[x][y * 3 + 1]);
				sourcedatatype_ptr->pack_normals[x].push_back(normals[x][y * 3 + 2]);
				sourcedatatype_ptr->pack_texcoord[x].push_back(texcoord[x][y * 2]);
				sourcedatatype_ptr->pack_texcoord[x].push_back(texcoord[x][y * 2 + 1]);

				// if (SourceDataType::CREATE_COLOR)
				// {
				// 	sourcedatatype_ptr->pack_color[x].push_back(sourcedatatype_ptr->indexdata.color[x][y * 4]);
				// 	sourcedatatype_ptr->pack_color[x].push_back(sourcedatatype_ptr->indexdata.color[x][y * 4 + 1]);
				// 	sourcedatatype_ptr->pack_color[x].push_back(sourcedatatype_ptr->indexdata.color[x][y * 4 + 2]);
				// 	sourcedatatype_ptr->pack_color[x].push_back(sourcedatatype_ptr->indexdata.color[x][y * 4 + 3]);
				// }

				if (sourcedatatype_ptr->create_animation)
				{
					for (int z = 0; z < sourcedatatype_ptr->max_joint_vector[x]; ++z)
					{
						sourcedatatype_ptr->pack_joints[x].push_back(sourcedatatype_ptr->indexdata.joints[x][y * sourcedatatype_ptr->max_joint_vector[x] + z]);
						sourcedatatype_ptr->pack_weights[x].push_back(sourcedatatype_ptr->indexdata.weights[x][y * sourcedatatype_ptr->max_joint_vector[x] + z]);
					}
				}

				for (int z = 0; z < positions[x].size() / 3; ++z)
				{
					if (canPack(sourcedatatype, x, y, z))
					{
						sourcedatatype_ptr->index[x][sourcedatatype_ptr->index[x].size() - 1].push_back(z);
					}
				}
			}
		}
	}
}
//
// bool GraphicReader::canPackNew(SourceDataType& sourcedatatype, int& x, int& y)
// {
// 	for (int z = 0; z < sourcedatatype_ptr->index[x].size(); ++z)
// 	{
// 		for (int w = 0; w < sourcedatatype_ptr->index[x][z].size(); ++w)
// 		{
// 			if (y == sourcedatatype_ptr->index[x][z][w])
// 			{
// 				return false;
// 			}
// 		}
// 	}

// 	return true;
// }

// bool GraphicReader::canPack(SourceDataType& sourcedatatype, int& x, int& y, int& z)
// {
// 	if (SourceDataType::CREATE_COLOR)
// 	{
// 		if
// 		(
// 			sourcedatatype_ptr->indexdata.color[x][y * 4] != sourcedatatype_ptr->indexdata.color[x][z * 4] ||
// 			sourcedatatype_ptr->indexdata.color[x][y * 4 + 1] != sourcedatatype_ptr->indexdata.color[x][z * 4 + 1] ||
// 			sourcedatatype_ptr->indexdata.color[x][y * 4 + 2] != sourcedatatype_ptr->indexdata.color[x][z * 4 + 2] ||
// 			sourcedatatype_ptr->indexdata.color[x][y * 4 + 3] != sourcedatatype_ptr->indexdata.color[x][z * 4 + 3]
// 		)
// 		{
// 			return false;
// 		}
// 	}

// 	if
// 	(
// 		sourcedatatype_ptr->indexdata.positions[x][y * 3] == sourcedatatype_ptr->indexdata.positions[x][z * 3] &&
// 		sourcedatatype_ptr->indexdata.positions[x][y * 3 + 1] == sourcedatatype_ptr->indexdata.positions[x][z * 3 + 1] &&
// 		sourcedatatype_ptr->indexdata.positions[x][y * 3 + 2] == sourcedatatype_ptr->indexdata.positions[x][z * 3 + 2] &&
// 		sourcedatatype_ptr->indexdata.texcoord[x][y * 2] == sourcedatatype_ptr->indexdata.texcoord[x][z * 2] &&
// 		sourcedatatype_ptr->indexdata.texcoord[x][y * 2 + 1] == sourcedatatype_ptr->indexdata.texcoord[x][z * 2 + 1] &&
// 		sourcedatatype_ptr->indexdata.normals[x][y * 3] == sourcedatatype_ptr->indexdata.normals[x][z * 3] &&
// 		sourcedatatype_ptr->indexdata.normals[x][y * 3 + 1] == sourcedatatype_ptr->indexdata.normals[x][z * 3 + 1] &&
// 		sourcedatatype_ptr->indexdata.normals[x][y * 3 + 2] == sourcedatatype_ptr->indexdata.normals[x][z * 3 + 2]
// 	)
// 	{
// 		if (sourcedatatype_ptr->create_animation)
// 		{
// 			for (int w = 0; w < sourcedatatype_ptr->max_joint_vector[x]; ++w)
// 			{
// 				if
// 				(
// 					sourcedatatype_ptr->indexdata.joints[x][y * sourcedatatype_ptr->max_joint_vector[x] + w] != sourcedatatype_ptr->indexdata.joints[x][z * sourcedatatype_ptr->max_joint_vector[x] + w] ||
// 					sourcedatatype_ptr->indexdata.weights[x][y * sourcedatatype_ptr->max_joint_vector[x] + w] != sourcedatatype_ptr->indexdata.weights[x][z * sourcedatatype_ptr->max_joint_vector[x] + w]
// 				)
// 				{
// 					return false;
// 				}
// 			}

// 			return true;
// 		}
// 		else
// 		{
// 			return true;
// 		}

// 	}
// 	else
// 	{
// 		return false;
// 	}
// }

void graphic_reader_fixAnimation(SourceDataType *sourcedatatype_ptr)
{
	for (int y = 0; y < sourcedatatype_ptr->armature_string_vector_size; ++y)
	{
		for (int x = 0; x < sourcedatatype_ptr->max_bonedata; ++x)
		{
			if (strcmp(sourcedatatype_ptr->armature_string_vector[y], sourcedatatype_ptr->bonedata_vector[x].bones_name_string[0]) == 0)
			{
				int y_index = y * sourcedatatype_ptr->max_frame * 16;

				for (int z = 0; z < sourcedatatype_ptr->max_frame; ++z)
				{
					int z_index = z * 16;

					// M4x4::inverse(sourcedatatype_ptr->armature_transform_vector, y_index + z_index);
					// M4x4::inverse(sourcedatatype_ptr->armature_transform_vector, y_index + z_index);
					sourcedatatype_ptr->armature_transform_vector[y_index + 3 + z_index] -= sourcedatatype_ptr->bonedata_vector[x].visual_bones_transform_float_vector[3];
					sourcedatatype_ptr->armature_transform_vector[y_index + 7 + z_index] -= sourcedatatype_ptr->bonedata_vector[x].visual_bones_transform_float_vector[7];
					sourcedatatype_ptr->armature_transform_vector[y_index + 11 + z_index] -= sourcedatatype_ptr->bonedata_vector[x].visual_bones_transform_float_vector[11];
					m4x4_inverse(sourcedatatype_ptr->armature_transform_vector, y_index + z_index);
				}
			}
		}
	}
}

// void GraphicReader::unPackIndex(SourceDataType& sourcedatatype)
// {
// 	for (int x = 0; x < sourcedatatype_ptr->object_name_vector.size(); ++x)
// 	{
// 		sourcedatatype_ptr->unpack_index.push_back({});

// 		for (int y = 0; y < sourcedatatype_ptr->indexdata.positions[x].size() / 3; ++y)
// 		{
// 			for (int z = 0; z < sourcedatatype_ptr->index[x].size(); ++z)
// 			{
// 				for (int w = 0; w < sourcedatatype_ptr->index[x][z].size(); ++w)
// 				{
// 					if (sourcedatatype_ptr->index[x][z][w] == y)
// 					{
// 						sourcedatatype_ptr->unpack_index[x].push_back(z);
// 						break;
// 					}
// 				}
// 			}
// 		}
// 	}
// }

// void GraphicReader::unPackVisualBones(SourceDataType& sourcedatatype)
// {
// 	for (int x = 0; x < sourcedatatype_ptr->object_name_vector.size(); ++x)
// 	{
// 		sourcedatatype_ptr->un_pack_visual_bones.push_back({});

// 		for (int y = 0; y < sourcedatatype_ptr->visual_bones_bonedata_vector_vector[x].size(); ++y)
// 		{
// 			std::vector<float>& visual_bones_transform_float_vector = sourcedatatype_ptr->visual_bones_bonedata_vector_vector[x][y].visual_bones_transform_float_vector;

// 			for (int z = 0; z < visual_bones_transform_float_vector.size(); ++z)
// 			{
// 				sourcedatatype_ptr->un_pack_visual_bones[x].push_back(visual_bones_transform_float_vector[z]);
// 			}
// 		}
// 	}
// }

// void GraphicReader::updateBones(SourceDataType& sourcedatatype)
// {
// 	std::vector<std::string> armature_string_vector;
// 	for (int i = 0; i < sourcedatatype_ptr->armature_string_vector.size(); ++i)
// 	{
// 		armature_string_vector.push_back("*" + sourcedatatype_ptr->armature_string_vector[i] + "*");
// 	}

// 	for (int x = 0; x < sourcedatatype_ptr->object_name_vector.size(); ++x)
// 	{
// 		sourcedatatype_ptr->skinning_bones.push_back({});
// 		sourcedatatype_ptr->animation_bones.push_back({});

// 		for (int z = 0; z < sourcedatatype_ptr->joints[x].size(); ++z)
// 		{
// 			int index = GraphicReader::matchString(sourcedatatype_ptr->joints[x][z], armature_string_vector, '*', '*');
// 			if (index != -1)
// 			{
// 				sourcedatatype_ptr->skinning_bones[x].push_back(z * 16);
// 				sourcedatatype_ptr->animation_bones[x].push_back(index * sourcedatatype_ptr->max_frame);
// 			}
// 		}
// 	}
// }
