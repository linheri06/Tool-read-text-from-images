//// Copyright (c) 2020 PaddlePaddle Authors. All Rights Reserved.
////
//// Licensed under the Apache License, Version 2.0 (the "License");
//// you may not use this file except in compliance with the License.
//// You may obtain a copy of the License at
////
////     http://www.apache.org/licenses/LICENSE-2.0
////
//// Unless required by applicable law or agreed to in writing, software
//// distributed under the License is distributed on an "AS IS" BASIS,
//// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//// See the License for the specific language governing permissions and
//// limitations under the License.
//#include "opencv2/core.hpp"
//#include "opencv2/imgcodecs.hpp"
//#include "opencv2/imgproc.hpp"
//#include <opencv2/highgui.hpp>
//#include <iostream>
//#include <vector>
//#include <map>
//#include "tinyxml2.h"
//#include <set>
//
//
//#include <include/args.h>
//#include <include/paddleocr.h>
//#include <include/paddlestructure.h>
//#include <paddle_engine.h>
//using namespace PaddleOCR;
//
//class Input {
//private:
//	std::string path;
//	std::string pathXml;
//	std::map<std::string, std::string> Dictionary;
//	std::set<std::string> setLabel;
//public:
//	Input() {};
//	void ConstructorInput(std::string path, const char* pathXml) {
//
//		this->path = path;
//		tinyxml2::XMLDocument doc;
//
//
//		if (doc.LoadFile(pathXml) != tinyxml2::XML_SUCCESS) {
//			std::cout << "Failed to load XML file." << std::endl;
//			//return;
//		}
//
//
//		std::map<std::string, std::string> imageDictionary;
//
//
//		tinyxml2::XMLElement* imageElement = doc.FirstChildElement("tagset")->FirstChildElement("image");
//		while (imageElement) {
//			const char* imageName = imageElement->FirstChildElement("imageName")->GetText();
//			const char* tag = imageElement->FirstChildElement("tag")->GetText();
//
//			std::string imageName1 = (std::string) imageName;
//			if (imageName && tag) {
//				// Add key-value
//				imageDictionary[imageName1] = tag;
//			}
//
//			// Next <image>
//			imageElement = imageElement->NextSiblingElement("image");
//		}
//
//		Dictionary = imageDictionary;
//
//		std::set<std::string> setLabel;
//		for (const auto& entry : Dictionary) {
//			setLabel.insert(entry.second);
//		}
//		this->setLabel = setLabel;
//	}
//
//	std::map<std::string, std::string> getDictionary() {
//		return Dictionary;
//	}
//
//	std::set<std::string> getSetLabels() {
//		return setLabel;
//	}
//	std::string getPath() {
//		return path;
//	}
//};
//
//
//class Paddle {
//private:
//	PaddleEngine pe;
//	std::string text;
//public:
//	Paddle() {}
//	void ConstructorPaddle(PaddleEngine pe) {
//		this->pe = pe;
//	}
//	void Read(cv::Mat img, std::string out_p) {
//		//google::ParseCommandLineFlags(&argc, &argv, true);
//		int ret;
//		std::string text;
//		double score;
//		cv::resize(img, img, cv::Size(), 1.5, 1.5);
//		std::string jsonstr;
//		std::cout << out_p << std::endl;
//		ret = pe.predict(img, jsonstr, text, score, "D:/piano/output1/" + out_p);
//
//		if (text == "") {
//			int padding = 300;
//			cv::Scalar border_color(255, 255, 255);
//			copyMakeBorder(img, img, padding, padding, padding, padding, cv::BORDER_CONSTANT, border_color);
//			cv::imshow("output", img);
//
//			int height = img.rows;
//			int width = img.cols;
//
//			int tile_height = 300;
//			int tile_width = 300;
//
//
//			for (int y = 0; y < height - tile_height; y += 150) {
//				for (int x = 0; x < width - tile_width; x += 150) {
//
//					cv::Rect roi(x, y, tile_width, tile_height);
//					cv::Mat tile = img(roi);
//
//					std::string text1 = "";
//					cv::resize(tile, tile, cv::Size(), 2.5, 2.5);
//					ret = pe.predict(tile, jsonstr, text1, score, "D:/piano/output1/" + out_p);
//					if (text1 != "" && text1.length() > 2) {
//						text = text + "\n" + text1;
//						ret = pe.predict(tile, jsonstr, text1, score, "D:/piano/output1/" + out_p);
//					}
//				}
//			}
//		}
//		this->text = text;
//	}
//
//
//	std::string getText() {
//		return text;
//	}
//};
//
////x
//class BrandPiano {
//private:
//	std::string text;
//	std::set<std::string> setLabel;
//	std::string brand;
//public:
//	BrandPiano() {}
//	void ConstructorBrandPiano(std::string text, std::set<std::string> setLabel) {
//		this->text = text;
//		this->setLabel = setLabel;
//	}
//
//	std::string tolowerstr(std::string text) {
//		std::string text1;
//		for (char i : text) {
//			char c = tolower(i);
//			text1 = text1 + c;
//		}
//		return text1;
//	}
//
//	void setBrand() {
//		std::string text1;
//		text = tolowerstr(text);
//		size_t pos = 0;
//		std::string token, brand;
//		int flag_ = 0;
//		while ((pos = text.find('\n')) != std::string::npos) {
//			token = text.substr(0, pos);
//			std::string b;
//			int flag = 0;
//			for (std::string i : setLabel) {
//				int f = 0, d = 0;
//				if (i == token) {
//					this->brand = i;
//					return;
//				}
//				for (char j : i) {
//					if (j == token[d]) {
//						d++;
//						f++;
//					}
//					else {
//						if (j == token[d + 1]) {
//							f++;
//							d = d + 2;
//						}
//					}
//					if (d > token.length()) break;
//				}
//				if (i.length() == token.length()) f++;
//				if (f > flag) {
//					flag = f;
//					b = i;
//				}
//			}
//			if (flag > flag_) {
//				flag_ = flag;
//				brand = b;
//				text1 = token;
//			}
//			text.erase(0, pos + 1);
//		}
//
//		for (std::string i : setLabel) {
//			std::string b;
//			int f = 0, d = 0, flag = 0;
//			if (i == text) {
//				this->brand = i;
//				return;
//			}
//			for (char j : i) {
//				if (j == text[d]) {
//					d++;
//					f++;
//				}
//				else {
//					if (j == text[d + 1]) {
//						f++;
//						d = d + 2;
//					}
//				}
//				if (d > text.length()) break;
//			}
//			if (i.length() == text.length()) f++;
//			if (f > flag_) {
//				flag_ = f;
//				brand = i;
//				text1 = text;
//			}
//		}
//		//std::cout << brand;
//		this->brand = brand;
//	}
//
//	std::string getBrand() {
//		return brand;
//	}
//};
//
//class Check {
//private:
//	std::string key;
//	std::string brand;
//	std::map<std::string, std::string> Dictionary;
//	std::string lable;
//public:
//	Check() {}
//	void ConstructorCheck(std::string brand, std::map<std::string, std::string> Dictionary, std::string path) {
//		this->brand = brand;
//		this->Dictionary = Dictionary;
//		this->key = path;
//	}
//	int checkPiano() {
//		std::map<std::string, std::string>::iterator it = Dictionary.find(key);
//		//std::cout << key;
//		if (it != Dictionary.end()) {
//			if (brand.find(it->second) != 18446744073709551615) {
//				std::cout << "Value: " << it->second << " Text: " << brand << std::endl;
//				//std::cout << "Key " << it->second << " exists in Dictionary with value " << text << std::endl;
//				this->lable = it->second;
//				return 1;
//			}
//			else {
//				std::cout << "Value: " << it->second << " Text: " << brand << std::endl;
//				//std::cout << "Key " << i << " exists in Dictionary, but the value is different." << std::endl;
//				return 0;
//			}
//		}
//		else {
//			std::cout << "Value: " << it->second << " Text: " << brand << std::endl;
//			//std::cout << "Key " << i << " does not exist in Dictionary." << std::endl;
//			return 0;
//		}
//		return 0;
//	}
//
//	std::string getLabel() {
//		return lable;
//	}
//
//};
//
//class Output {
//private:
//	std::string lable;
//	std::string brand;
//	std::string out_path;
//public:
//	Output() {};
//	void ConstructorOutput(std::string lable, std::string brand, std::string out_path) {
//		this->lable = lable;
//		this->brand = brand;
//		this->out_path = out_path;
//	}
//
//	void saveImg() {
//		cv::Mat img = cv::imread(out_path, cv::IMREAD_COLOR);
//		cv::putText(img, lable, cv::Point(100, 130), cv::FONT_HERSHEY_SIMPLEX, 1, CV_RGB(255, 0, 0), 2);
//		cv::putText(img, brand, cv::Point(100, 100), cv::FONT_HERSHEY_SIMPLEX, 1, CV_RGB(0, 255, 0), 2);
//		cv::imwrite(out_path, img);
//	}
//};
//
//
//class Controller {
//private:
//	Input in;
//	Paddle pa;
//	BrandPiano b;
//	Check check;
//	Output out;
//	int s;
//public:
//	Controller() {};
//	Controller(std::string path, const char* pathXml, PaddleEngine pe) {
//		in.ConstructorInput(path, pathXml);
//		pa.ConstructorPaddle(pe);
//	}
//
//	int Score() {
//		int s = 0;
//
//		//google::ParseCommandLineFlags(&argc, &argv, true);
//		std::vector<cv::String> cv_all_img_names;
//		cv::glob(in.getPath(), cv_all_img_names);
//		std::cout << "total images num: " << cv_all_img_names.size() << std::endl;
//		for (cv::String i : cv_all_img_names) {
//			cv::Mat img = cv::imread(i, cv::IMREAD_COLOR);
//			std::string a = i.c_str();
//			a = a.erase(0, 21);
//			//std::cout <<a.erase(0, 21) << std::endl;
//			/*imshow("", img);
//			cv::waitKey(0);*/
//			pa.Read(img, a);
//			//std::cout << "a" << std::endl;
//			b.ConstructorBrandPiano(pa.getText(), in.getSetLabels());
//			b.setBrand();
//			std::cout << "Brand:" << b.getBrand() << std::endl;
//			check.ConstructorCheck(b.getBrand(), in.getDictionary(), a);
//			int d = check.checkPiano();
//			std::cout << d << std::endl;
//			s = s + d;
//			out.ConstructorOutput(check.getLabel(), b.getBrand(), "D:/piano/output1/" + a);
//			out.saveImg();
//		}
//		this->s = s;
//		return s;
//	}
//};
//
//
//
//int main(int argc, char **argv) {
//	int ret = 0;
//
//	PaddleEngine pe;
//	pe.configRecognizer("--rec_char_dict_path=E:/PaddleOCR2.6/PaddleOCR/ppocr/utils/en_dict.txt \
//--layout_model_dir=E:/PaddleOCR2.6/PaddleOCR/paddleocr/paddle_layout_model/picodet_lcnet_x1_0_fgd_layout_infer --layout_dict_path=E:/PaddleOCR2.6/PaddleOCR/paddleocr/paddle_layout_model/picodet_lcnet_x1_0_fgd_layout_infer/layout_table_dict.txt \
//--table_model_dir=E:/PaddleOCR2.6/PaddleOCR/paddleocr/paddle_table_model/ch_ppstructure_mobile_v2.0_SLANet_infer --table_char_dict_path=E:/PaddleOCR2.6/PaddleOCR/paddleocr/paddle_table_model/ch_ppstructure_mobile_v2.0_SLANet_infer/table_structure_dict_ch.txt");
//
//	pe.initRecognizer("D:/PaddleOCR/ch_lite/en_PP-OCRv3_det_infer", "D:/PaddleOCR/inference/en_PP-OCRv3_rec_infer", "D:/PaddleOCR/inference/ch_ppocr_mobile_v2.0_cls_slim_infer");
//
//	////cv::Mat img = cv::imread("D:/Downloads/scene/SceneTrialTest/sml_01.08.2002/IMG_1197_1.JPG", cv::IMREAD_COLOR);
//	////cv::Mat img = cv::imread("D:/Downloads/scene/SceneTrialTest/ryoungt_05.08.2002/Pict0045.JPG", cv::IMREAD_COLOR);
//	//cv::Mat img = cv::imread("D:/piano/grand_piano/1.jpg", cv::IMREAD_COLOR);//IMG_100000077
//	///*img.convertTo(img, -1, 1, 50);
//	//img.convertTo(img, -1, 0.85, 0)*/;
//	//cv::resize(img, img, cv::Size(),2.5,2.5);
//	////cv::threshold(img, img, 50, 255, cv::THRESH_BINARY);
//	////cv::Mat kernel1 = (cv::Mat_<double>(3, 3) << 0, -1, 0, -1, 4, -1, 0, -1, 0);
//	////cv::filter2D(img, img,-1, kernel1, cv::Point(-1, -1), 0, 4);
//	////cv::filter2D(img, img, -1, kernel1, cv::Point(-1, -1), 0, 4);
//	//std::string text;
//	//double score;
//
//	//std::string jsonstr;
//	//ret = pe.predict(img, jsonstr, text, score, "D:/piano/output1/xoa.jpg");
//	////std::cout << "text: " << text << " - " << score << std::endl; 
//
//
//	Controller control = Controller("D:/piano/grand_piano", "D:/piano/label.xml", pe);
//	//std::cout << "------------ryoungt_05.08.2002--------------" << std::endl;
//	float s1 = control.Score();
//	std::cout << s1 << std::endl;
//
//
//	/*std::cout << "------------ryoungt_05.08.2002--------------" << std::endl;
//	float s1 = score("D:/Downloads/scene/SceneTrialTest/ryoungt_05.08.2002", argc, argv, pe);
//	std::cout << s1<< std::endl;
//
//	std::cout << "------------ryoungt_13.08.2002--------------" << std::endl;
//	float s2 = score("D:/Downloads/scene/SceneTrialTest/ryoungt_13.08.2002", argc, argv, pe);
//	std::cout << s2<< std::endl;
//
//	std::cout << "------------sml_01.08.2002--------------" << std::endl;
//	float s3 = score("D:/Downloads/scene/SceneTrialTest/sml_01.08.2002", argc, argv, pe);
//	std::cout << s3<< std::endl;
//
//	std::cout << "D:/Downloads/scene/SceneTrialTest/ryoungt_05.08.2002: " << s1<<std::endl;
//	std::cout << "D:/Downloads/scene/SceneTrialTest/ryoungt_13.08.2002: " << s2 << std::endl;
//	std::cout << "D:/Downloads/scene/SceneTrialTest/sml_01.08.2002: " << s3 << std::endl;
//	std::cout << "Score: " << (s1 + s2 + s3) / 3 << std::endl;*/
//	return ret;
//}
//
