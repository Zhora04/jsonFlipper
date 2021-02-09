#include <iostream>
#include <vector>
#include <fstream>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <nlohmann/json.hpp>
using namespace std;
using namespace cv;
using namespace nlohmann;

//void ForOneImage(string path1, string path2) {
//	cv::Mat img = imread(path2);
//	int rows = img.size().width;
//	fstream file(path1);
//	json j;
//	j << file;
//	vector<int> v;
//	bool t = 0;
//	for (auto i : j["items"]["items"][0]["data"]["polygon"]) {
//		v.push_back(abs(rows * t - int(i)));
//		t = !t;
//	}
//	for (int i = 0; i < v.size(); i++) {
//		j["items"]["items"][0]["data"]["polygon"][i] = v[i];
//	}
//	fstream newFile(path2 + ".json", ios::out);
//	newFile << j;
//
//}

void makeJson(string& json_path, string& img_path)
{
	Mat img = imread(img_path);
	fstream file(json_path);
	json j;
	file >> j;
	vector<int> cords, res_cords;
	for (int i : j["items"]["items"][0]["data"]["polygon"]) cords.push_back(i);
	// 0, 2, 4, 6 -> x
	// 1, 3, 5, 7 -> y
	for (int i = 0; i < cords.size(); i++)
	{
		// cords[i + 1] = const
		if (i & 1) res_cords.push_back(cords[i]);
		else res_cords.push_back(img.cols - cords[i]);
	}
	for (int i = 0; i < cords.size(); i++)
		j["items"]["items"][0]["data"]["polygon"][i] = res_cords[i];
	fstream newFile(img_path + ".json", ios::out);
	newFile << j;
}

int main()
{
	vector<string> json_paths, norm_flip_img_paths;
	glob("C:\\Users\\Þวละ\\Downloads\\img_json", json_paths);
	glob("C:\\Users\\Þวละ\\Desktop\\normalized_flipped_images", norm_flip_img_paths);
	for (int i = 1, id = 0; i < json_paths.size(); i += 2, id++)
	{
		makeJson(json_paths[i], norm_flip_img_paths[id]);
	}
}
