static const uint32_t pipeline[] =
{
	//vert frag
	0, 0
};

static const uint8_t image[] =
{
	//mipmap line
	// 1 + 2 +
	// 4 + 8

	0 + 2 +
	0 + 8
};

static const uint32_t model[] =
{
	0
};

// static const void config[];

void gen_file()
{
	FILE *file = fopen(NALI_HOME "pipeline.bin", "wb");
	fwrite(pipeline, sizeof(char), sizeof(pipeline), file);
	fclose(file);

	file = fopen(NALI_HOME "model.bin", "wb");
	fwrite(model, sizeof(char), sizeof(model), file);
	fclose(file);

	file = fopen(NALI_HOME "image.bin", "wb");
	fwrite(model, sizeof(char), sizeof(model), file);
	fclose(file);
}