#include<iostream>
#include<vector>
#include<time.h>
#include<stdlib.h>
#include<fstream>
#include<string>
#include<set>

#define Random(x) rand()%x
using namespace std;
string path = "./sudoku.txt";
ofstream fout(path.c_str());
bool valid(const vector<vector<int>> &shuju, const int hang, const int lie, const int &num) {
	//在这里就是一个一个比对 因为后面的没有生成  只要判断已经生成的干扰项

	//所以 对于行、列、宫 三个条件 只需要到自己所对应的行去就好了

	//先检查同一行的有没有一样的 
	for (int j = 0; j < lie; j++) {
		if (shuju.at(hang).at(j) == num) {
			return false;
		}
	}
	//检查列有没有相同的
	for (int i = 0; i < hang; i++) {
		if (shuju.at(i).at(lie) == num) {
			return false;
		}
	}

	//检查宫格

	int block_hang_start = (hang / 3) * 3;
	int block_hang_end = block_hang_start + 3;

	int block_lie_start = (lie / 3) * 3;
	int block_lie_end = block_lie_start + 3;


	for (int i = block_hang_start; i < block_hang_end; i++) {
		for (int j = block_lie_start; j < block_lie_end; j++) {
			if (shuju.at(i).at(j) == num) {
				return false;
			}
		}
	}
	return true;
}


bool shengcheng(vector<vector<int>> &shuju, const set<int> &shu) {

	int hang(0), lie(0), suiji_number(0);
	vector<set<int>> zancun;
	set<int> houxuan_number(shu);
	while (hang < 9) {
		while (lie < 9) {

			while (!houxuan_number.empty()) {
				suiji_number = Random(9) + 1;
				//cout << "suiji_number " << suiji_number<<endl;
				auto itear = houxuan_number.find(suiji_number);
				if (itear != houxuan_number.end()) {
					//不是end 说明这个数据在set中是存在的
					houxuan_number.erase(itear);
				}
				else
				{
					//随机找到的这个数是不存在在set中的数字
					continue;
				}
				//已经生成了随机数
				if (valid(shuju, hang, lie, suiji_number)) {
					//如果成功了 将shuju的i,j置为当前的数
					shuju.at(hang).at(lie) = suiji_number;
					//之后 移动行、列  准备接收新的东西
					if (hang == 8 && lie == 8) {
						//已经接收完毕
						return true;
					}
					if (lie == 8 && hang < 8)
					{
						lie = 0;
						hang++;

					}
					else
					{
						lie++;

					}
					zancun.push_back(houxuan_number);
					houxuan_number = shu;
					break;//跳出找随机数的循环
				}
				else
				{
					continue;
				}
			}
			if (houxuan_number.empty()) {
				//如果候选的number为空了  那么 进行回溯
				shuju.at(hang).at(lie) = 0;//将当前位置置零
				if (lie > 0 && lie <= 8) {
					lie--;
				}
				if (lie == 0 && hang>0)
				{
					lie = 8;
					hang--;
				}
				if (lie == 0 && hang == 0) {
					cout << "没有结果" << endl;
					return false;
				}
				auto iend = zancun.end();
				houxuan_number = *(iend - 1);
				zancun.pop_back();
			}
		}
	}
}
void print(vector<vector<int>> &shuju) {

	int sizeofshuju = shuju.size();
	int sizeofshuju1 = shuju.at(1).size();
	for (int i = 0; i < sizeofshuju; i++) {
		for (int j = 0; j < sizeofshuju1; j++) {
			//cout << shuju.at(i).at(j) << " ";
			fout << shuju.at(i).at(j);
			if (j != (sizeofshuju1 - 1)) {
				fout << " ";
			}
		}
		if (i != (sizeofshuju - 1)) {
			//cout << endl;
			//fout << endl;
			fout << "\n";
		}
	}
}
void qingkong(vector<vector<int>> &shuju) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			shuju.at(i).at(j) = 0;
		}
	}
}

int main(int argc, char* argv[]) {
	vector<vector<int>> shuju(9, vector<int>(9, 0));
	srand((unsigned)time(NULL));
	set<int > shu;
	for (int i = 1; i < 10; i++) {
		shu.insert(i);
	}
	int cishu(atoi(argv[2])), i(0);

	if (strcmp(argv[1],"-c")==0&& cishu > 0) {
		while (i < cishu) {
			if (shengcheng(shuju, shu)) {
				print(shuju);
				if (i != (cishu - 1)) {
					//cout << endl;
					//cout << endl;
					//fout << endl;
					//fout << endl;
					fout << "\n";
					fout << "\n";
				}
				else
				{
					break;
				}
			}
			qingkong(shuju);
			i++;
		}
	}
	else
	{
		cout << "输入错误" << endl;
	}
	//system("pause");
	fout.close();

	return 0;
}
