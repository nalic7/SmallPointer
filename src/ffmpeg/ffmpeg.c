AVFormatContext* avformatcontext = NULL;
AVCodecContext* avcodeccontext = NULL;
const AVCodec* avcodec = NULL;
AVFrame* avframe = NULL;
AVPacket avpacket;
// struct SwsContext* swscontext = NULL;
int video_stream_index = -1;

void ffmpeg_read(const char *filename)
{
	avformat_network_init();

	if (avformat_open_input(&avformatcontext, filename, NULL, NULL) < 0)
	{
		error("avformat_open_input")
	}

	if (avformat_find_stream_info(avformatcontext, NULL) < 0)
	{
		error("avformat_find_stream_info")
	}

	int video_stream_index = av_find_best_stream(avformatcontext, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
	if (video_stream_index < 0)
	{
		error("av_find_best_stream %d", video_stream_index)
	}
	// for (int i = 0; i < avformatcontext->nb_streams; i++)
	// {
	// 	if (avformatcontext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
	// 	{
	// 		video_stream_index = i;
	// 		break;
	// 	}
	// }
	info("video_stream_index %d", video_stream_index)

	avcodec = avcodec_find_decoder(avformatcontext->streams[video_stream_index]->codecpar->codec_id);
	if (!avcodec)
	{
		error("avcodec_find_decoder")
	}

	avcodeccontext = avcodec_alloc_context3(avcodec);
	if (!avcodeccontext)
	{
		error("avcodec_alloc_context3")
	}

	if (avcodec_parameters_to_context(avcodeccontext, avformatcontext->streams[video_stream_index]->codecpar) < 0)
	{
		error("avcodec_parameters_to_context")
	}

	if (avcodec_open2(avcodeccontext, avcodec, NULL) < 0)
	{
		error("avcodec_open2")
	}

	avframe = av_frame_alloc();
}

uint8_t* ffmpeg_png(uint32_t* width_p, uint32_t* height_p)
{
	if (av_read_frame(avformatcontext, &avpacket) < 0)
	{
		error("av_read_frame")
	}

	if (avcodec_receive_frame(avcodeccontext, avframe) < 0)
	{
		error("avcodec_receive_frame")
	}

	*width_p = avframe->width;
	*height_p = avframe->height;

	uint8_t* data_p = (uint8_t*)malloc(avframe->width * avframe->height * 4);

	int num_bytes = av_image_get_buffer_size(AV_PIX_FMT_RGBA, avframe->width, avframe->height, 1);
	av_image_copy_to_buffer(data_p, num_bytes, (const uint8_t* const*)avframe->data, avframe->linesize, AV_PIX_FMT_RGBA, avframe->width, avframe->height, 1);

	av_packet_unref(&avpacket);

	return data_p;
}

void ffmpeg_clean()
{
	av_frame_free(&avframe);
	avcodec_free_context(&avcodeccontext);
	avformat_close_input(&avformatcontext);
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

// 		if (avcodec_receive_frame(avcodeccontext, avframe) == 0)
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
