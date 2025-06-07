// static const uint32_t pipeline[] =
// {
// 	//vert frag
// 	0, 0,
// 	1, 1
// };

// static const uint8_t image[] =
// {
// 	//mipmap line
// 	1 + 2 +
// 	4 + 8

// 	// 1 + 0 +
// 	// 4 + 0

// 	// 0 + 2 +
// 	// 0 + 8
// };

// static const uint32_t model[] =
// {
// 	0
// };

// static const void config[];
void g_write()
{
	remove(NALI_F_HOME_ASSET);
	gkf_write();
	gm_write();

	// FILE *file = fopen(NALI_F_HOME "pipeline.bin", "wb");
	// fwrite(pipeline, sizeof(char), sizeof(pipeline), file);
	// fclose(file);

	// file = fopen(NALI_F_HOME "model.bin", "wb");
	// fwrite(model, sizeof(char), sizeof(model), file);
	// fclose(file);

	// file = fopen(NALI_F_HOME "image.bin", "wb");
	// fwrite(image, sizeof(char), sizeof(image), file);
	// fclose(file);
}