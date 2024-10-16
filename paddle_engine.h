#pragma once

#ifdef PADDLE_ENGINE_EXPORTS
#define PADDLE_ENGINE_API __declspec(dllexport)
#else
#define PADDLE_ENGINE_API __declspec(dllimport)
#endif

#include "opencv2/core.hpp"


#include <iostream>
#include <vector>
#include <winerror.h>

#include <include/args.h>
#include <include/paddleocr.h>
#include <include/paddlestructure.h>

#include <opencv2/highgui.hpp>


class PADDLE_ENGINE_API PaddleEngine
{
private:
	void* recognizer;
	void* structureDetector;

public:
	int initRecognizer(std::string det_model_path, std::string rec_model_path, std::string cls_model_path);
	int configRecognizer(std::string opt);
	int detect(cv::Mat img, std::string &jsonResult);
	int readText(cv::Mat img, std::string &text, double &score, bool det, bool rec, bool cls);
	int predict(cv::Mat img, std::string &jsonResult, std::string &text, double &score, std::string path);
	int structure(cv::Mat img, bool layout, bool table, std::string &jsonResult);
};