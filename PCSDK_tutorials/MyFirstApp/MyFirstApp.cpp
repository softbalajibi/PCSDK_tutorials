﻿// MyFirstApp.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "util_render.h"
#include "util_pipeline.h"


int _tmain(int argc, _TCHAR* argv[])
{
	UtilPipeline pipeline;
	pipeline.EnableImage(PXCImage::COLOR_FORMAT_RGB32, 1280, 720);	// default 640x480
	pipeline.EnableImage(PXCImage::COLOR_FORMAT_DEPTH);
	pipeline.Init();

	UtilRender color_render(L"Color Stream");
	UtilRender depth_render(L"Depth Stream");

	for (;;) {
		if (!pipeline.AcquireFrame(true)) break;

		PXCImage *color_image = pipeline.QueryImage(PXCImage::IMAGE_TYPE_COLOR);
		PXCImage *depth_image = pipeline.QueryImage(PXCImage::IMAGE_TYPE_DEPTH);
		if (!color_render.RenderFrame(color_image)) break;
		if (!depth_render.RenderFrame(depth_image)) break;
		
		pipeline.ReleaseFrame();
	}
	pipeline.Close();

	return 0;
}
