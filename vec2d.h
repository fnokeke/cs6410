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
		int* get(int i, int j);
		int* operator[](int i);	
		void resize(int row, int col);
		void set_sequence(std::string seq);
};


//class implementation
//for vec2d

vec2d::vec2d(int size):size(size),vec(size) {}

vec2d::vec2d(int row_len, int col_len):
			size(row_len * col_len),
			vec(row_len * col_len),
			row_len(row_len),
			col_len(col_len) {}
			
int* vec2d::get(int i, int j) {
	return &vec[i*j];
}

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

void vec2d::set_sequence(std::string seq) {
	if (seq == "gliders") {
	
	}
	else if (seq == "guns") {
		
	}
}

#endif
 
