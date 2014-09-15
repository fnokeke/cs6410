#include <vector>
#include <string>
#include <cassert>

#ifndef VEC2D
#define VEC2D

using namespace std;

class vec2d {
	private:
		int size;
		vector<int> vec;
		int row_len;
		int col_len;
		
	public:
		vec2d(int size);
		vec2d(int row_len, int col_len);
		int get_row_len(){return row_len;}
		int get_col_len(){return col_len;}
		int* operator[](int i);	
		void resize(int row, int col);
};


//class implementation
//for vec2d

vec2d::vec2d(int size):size(size),vec(size, 0) {}

vec2d::vec2d(int row_len, int col_len):
			size(row_len * col_len),
			vec(row_len * col_len, 0),
			row_len(row_len),
			col_len(col_len) {}

int* vec2d::operator[](int i){
		assert (size <= (int) vec.capacity());
		assert (i*row_len < size);
		//cout << "i=" << i << ";" << "row_len="<<row_len << ";" << "size=" << size << endl;
		assert (i*row_len + row_len <= size);
		return &vec[i*row_len];
}

void vec2d::resize(int i, int j) {
	vec.resize(i * j);
}

//function outside class 
void set_sequence(vec2d& vec, string seq) {
	//Generates a random state 
	int row = vec.get_row_len();
	int col = vec.get_col_len();
	if (seq == "random") {
		srand(time(NULL));
		for(int j = 0; j < row; j++)
        {
			for (int i = 0; i < col; i++)
				vec[j][i] = rand() % 2;
		}	
	}
	//Generates a glider state 
	else if (seq == "gliders") {
		if (row >=5 && col >= 5) {
			vec[1][2] = 1;
			vec[2][3] = 1;
			vec[3][1] = 1;
			vec[3][2] = 1;
			vec[3][3] = 1;
		}
	}
	//Generates a gun state 
	else if (seq == "guns") {
		
	}
}


#endif
 
