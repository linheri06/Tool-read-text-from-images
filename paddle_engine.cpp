#include "paddle_engine.h"
#include <iostream>
#include <vector>
#include <winerror.h>

#include <include/args.h>
#include <include/paddleocr.h>
#include <include/paddlestructure.h>

#include <opencv2/highgui.hpp>

using namespace PaddleOCR;

int PaddleEngine::initRecognizer(std::string det_model_path, std::string rec_model_path, std::string cls_model_path)
{
	int ret = ERROR_SUCCESS;
	FLAGS_det_model_dir = det_model_path;
	FLAGS_rec_model_dir = rec_model_path;
	FLAGS_cls_model_dir = cls_model_path;

	recognizer = new PPOCR();
	structureDetector = new PaddleStructure();
	return ret;
}

int PaddleEngine::configRecognizer(std::string opt)
{
	int ret = ERROR_SUCCESS;
	std::cout << "opt : " << opt << std::endl;
	std::vector<std::string> args;
	std::istringstream iss(opt);
	std::string token;
	while (iss >> token) {
		args.push_back(token);
	}
	int argc = args.size() + 1;
	char ** argv = new char*[argc];
	argv[0] = new char[1]{ '\0' };
	for (int i = 0; i < args.size(); i++)
	{
		argv[i + 1] = new char[args[i].length() + 1];
		strcpy(argv[i + 1], args[i].c_str());
		argv[i + 1][args[i].length()] = '\0';
	}
	google::ParseCommandLineFlags(&argc, &argv, true);
	std::cout << "FLAGS_rec_char_dict_path : " << FLAGS_rec_char_dict_path << std::endl;
	std::cout << "layout_model_dir : " << FLAGS_layout_model_dir << std::endl;
	std::cout << "table_model_dir : " << FLAGS_table_model_dir << std::endl;
	return ret;
}

int PaddleEngine::detect(cv::Mat img, std::string &jsonResult)
{
	int ret = ERROR_SUCCESS;
	PPOCR* ppocr = static_cast<PPOCR*>(recognizer);
	std::vector<OCRPredictResult> ocrPredictResult = ppocr->ocr(img, true, false, false);
	jsonResult = Utility::OCRPredictResult2JsonStr(ocrPredictResult);
	return ret;
}

int PaddleEngine::readText(cv::Mat img, std::string &text, double &score, bool det, bool rec, bool cls)
{
	int ret = ERROR_SUCCESS;
	PPOCR* ppocr = static_cast<PPOCR*>(recognizer);
	text = "";
	score = -1;
	ret = ppocr->ocr(img, text, score, det, rec, cls);
	return ret;
}

int PaddleEngine::predict(cv::Mat img, std::string &jsonResult, std::string &text, double &score, std::string path)
{
	int ret = ERROR_SUCCESS;
	PPOCR* ppocr = static_cast<PPOCR*>(recognizer);
	std::vector<OCRPredictResult> ocrPredictResult = ppocr->ocr(img, true, true, true);
	if (ocrPredictResult.size() > 0) {
		score = 0;
		for (int i = 0; i < ocrPredictResult.size(); i++) {
			text += ocrPredictResult[i].text;
			if (i < ocrPredictResult.size() - 1) {
				text += "\n";
			}
			score += ocrPredictResult[i].score;
		}
		score /= ocrPredictResult.size();

	}

	//std::cout << path;
	if (score < 0.4 || true) {
		Utility::VisualizeBboxes(img, ocrPredictResult, path);
		cv::Mat img1 = cv::imread(path, cv::IMREAD_COLOR);
		//resize(img1, img1, cv::Size(), 0.5, 0.5);
		//imshow("output", img1);
		cv::waitKey(0);

		jsonResult = Utility::OCRPredictResult2JsonStr(ocrPredictResult);
		cv::putText(img1, jsonResult, cv::Point(100, 190), cv::FONT_HERSHEY_SIMPLEX, 0.5, CV_RGB(0, 255, 255), 2);
		cv::imwrite(path, img1);
	}
	return ret;
}

//int PaddleEngine::predict(cv::Mat img, std::string &jsonResult)
//{
//	int ret = ERROR_SUCCESS;
//	PPOCR* ppocr = static_cast<PPOCR*>(recognizer);
//	std::vector<OCRPredictResult> ocrPredictResult = ppocr->ocr(img, true, true, false);
//
//	//Utility::print_result(ocrPredictResult);
//	Utility::VisualizeBboxes(img, ocrPredictResult, "D:/Downloads/scene/SceneTrialTest/output/predict_result.jpg");
//	cv::Mat img1 = cv::imread("D:/Downloads/scene/SceneTrialTest/output/predict_result.jpg", cv::IMREAD_COLOR);
//	cv::resize(img1, img1, cv::Size(), 0.3, 0.3);
//	imshow("output", img1);
//	cv::waitKey(0);
//	jsonResult = Utility::OCRPredictResult2JsonStr(ocrPredictResult);
//	return ret;
//}

int PaddleEngine::structure(cv::Mat img, bool layout, bool table, std::string &jsonResult) {
	int ret = ERROR_SUCCESS;
	PaddleStructure* ppStructure = static_cast<PaddleStructure*>(structureDetector);
	std::vector<StructurePredictResult> structure_results = ppStructure->structure(img, layout, table, false);

	/*cv::Mat drawImg = img.clone();
	for (int j = 0; j < structure_results.size(); j++) {
		cv::Rect rect(structure_results[j].box[0], structure_results[j].box[1], structure_results[j].box[2] - structure_results[j].box[0], structure_results[j].box[3] - structure_results[j].box[1]);
		cv::rectangle(drawImg, rect, cv::Scalar(255, 0, 0), 5, 8);

		for (int i = 0; i < structure_results[j].cell_box.size(); i++) {
			std::cout << "structure_results[j].cell_box = " << structure_results[j].cell_box[i].size() << std::endl;
			std::vector<int> structure_cell_box = Utility::xyxyxyxy2xyxy(structure_results[j].cell_box[i]);
			std::cout << structure_cell_box[0] << ","
				<< structure_cell_box[1] << ","
				<< structure_cell_box[2] << ","
				<< structure_cell_box[3] << std::endl;
			cv::Rect box_rect(structure_cell_box[0] + structure_results[j].box[0], structure_cell_box[1] + structure_results[j].box[1], structure_cell_box[2] - structure_cell_box[0], structure_cell_box[3] - structure_cell_box[1]);
			cv::rectangle(drawImg, box_rect, cv::Scalar(0, 255, 0), 1);
		}
	}
	cv::resize(drawImg, drawImg, cv::Size(), 0.3, 0.3);
	cv::imshow("drawImg", drawImg);
	cv::waitKey();*/

	jsonResult = Utility::StructurePredictResult2JsonStr(structure_results);
	return ret;
}