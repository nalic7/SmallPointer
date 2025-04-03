static AVFormatContext *avformatcontext_p = NULL;
static AVCodecContext *avcodeccontext_p = NULL;
static const AVCodec *avcodec_p = NULL;
static AVFrame *avframe_p = NULL;
static AVPacket avpacket;
// static struct SwsContext *swscontext = NULL;
static int video_stream_index = -1;

void ffmpeg_read(const char *filename)
{
	nali_info("avformat_network_init %d", avformat_network_init())

	nali_info("avformat_open_input %d", avformat_open_input(&avformatcontext_p, filename, NULL, NULL))

	nali_info("avformat_find_stream_info %d", avformat_find_stream_info(avformatcontext_p, NULL))

	int video_stream_index;
	nali_info("av_find_best_stream %d", video_stream_index = av_find_best_stream(avformatcontext_p, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0))

	nali_info("avcodec_find_decoder %p", avcodec_p = avcodec_find_decoder(avformatcontext_p->streams[video_stream_index]->codecpar->codec_id))

	nali_info("avcodec_alloc_context3 %p", avcodeccontext_p = avcodec_alloc_context3(avcodec_p))

	nali_info("avcodec_parameters_to_context %d", avcodec_parameters_to_context(avcodeccontext_p, avformatcontext_p->streams[video_stream_index]->codecpar))

	nali_info("avcodec_open2 %d", avcodec_open2(avcodeccontext_p, avcodec_p, NULL))

	nali_info("av_frame_alloc %p", avframe_p = av_frame_alloc())
}

uint8_t *ffmpeg_png(uint32_t *width_p, uint32_t *height_p)
{
	nali_info("av_read_frame %d", av_read_frame(avformatcontext_p, &avpacket))

	nali_info("avcodec_send_packet %d", avcodec_send_packet(avcodeccontext_p, &avpacket))

	nali_info("avcodec_receive_frame %d", avcodec_receive_frame(avcodeccontext_p, avframe_p))

	*width_p = avframe_p->width;
	*height_p = avframe_p->height;

	// uint8_t *data_p = (uint8_t *)malloc(avframe_p->width * avframe_p->height * 4);

	int num_bytes = av_image_get_buffer_size(AV_PIX_FMT_RGBA, avframe_p->width, avframe_p->height, 1);
	uint8_t *data_p = (uint8_t *)malloc(num_bytes);
	nali_info("av_image_copy_to_buffer %d", av_image_copy_to_buffer(data_p, num_bytes, (const uint8_t * const *)avframe_p->data, avframe_p->linesize, AV_PIX_FMT_RGBA, avframe_p->width, avframe_p->height, 1))

	// data_p[0] = 255;
	// data_p[1] = 0;
	// data_p[2] = 0;
	// data_p[3] = 255;

	av_packet_unref(&avpacket);

	return data_p;
}

void ffmpeg_clean()
{
	av_frame_free(&avframe_p);
	avframe_p = NULL;
	avcodec_free_context(&avcodeccontext_p);
	avcodeccontext_p = NULL;
	avformat_close_input(&avformatcontext_p);
	avformatcontext_p = NULL;
}

// void decode()
// {
// 	if (av_read_frame(avformatcontext, &avpacket) < 0)
// 	{
// 		error("av_read_frame")
// 	}

// 	if (avpacket.stream_index == video_stream_index)
// 	{
// 		if (avcodec_send_packet(avcodeccontext, &avpacket) < 0)
// 		{
// 			error("avcodec_send_packet")
// 		}

// 		if (!avcodec_receive_frame(avcodeccontext, avframe))
// 		{
// 			swscontext = sws_getContext
// 			(
// 				avframe->width, avframe->height, avcodeccontext->pix_fmt,
// 				avframe->width, avframe->height, AV_PIX_FMT_RGBA,
// 				SWS_BICUBIC, NULL, NULL, NULL
// 			);

// 			AVFrame* rgbaFrame = av_frame_alloc();
// 			rgbaFrame->width = avframe->width;
// 			rgbaFrame->height = avframe->height;
// 			rgbaFrame->format = AV_PIX_FMT_RGBA;

// 			av_frame_get_buffer(rgbaFrame, 32);
// 			sws_scale(swscontext, (const uint8_t* const*)avframe->data, avframe->linesize, 0, avframe->height, rgbaFrame->data, rgbaFrame->linesize);
// 		}
// 	}

// 	av_packet_unref(&avpacket);
// }
