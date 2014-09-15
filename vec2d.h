#include <vector>
#include <string>
#include <iostream>
#include <cassert>

#ifndef VEC2D
#define VEC2D

#define FACTOR 2

using namespace std;

class vec2d {
	private:
		int col_index;
		int row_index;
		int col_len;
		int row_len;
		int size;
		vector<int> vec;

	public:
		vec2d(int rlen, int clen);
		int get_col_len(){return col_len;}
		int get_row_len(){return row_len;}
		int get_size(){return vec.size();}
		vector<int> get_vec(){return vec;}
		void set_vec(vector<int>& v);
		void set_index(int r, int c);
		int* operator[](int i);	
		void resize();
};

//
//class implementation
//

void vec2d::set_index(int r, int c) {
	row_index = r;
	col_index = c;
}


vec2d::vec2d(int rlen, int clen):
			col_index(0),
			row_index(0),
			col_len(clen), 
			row_len(rlen),
			size(rlen * clen), 
			vec(rlen * clen, 0) {}

int* vec2d::operator[](int i){
		//assert (size <= (int) vec.capacity());
		///assert (i*row_len <= size);
		//cout << "i=" << i << ";" << "row_len="<<row_len << ";" << "size=" << size << endl;
		//assert (i*row_len + row_len <= size);
		return &vec[i*row_len];
}

void vec2d::resize() {
	row_len *= FACTOR;
	col_len *= FACTOR;
	int new_size = row_len * col_len;
	cout << "now resizing to " << new_size << endl;
	vec = vector<int>(new_size,0);
}

//This function checks if the array has any cells at the 
//all of the four corners and this state can help determine
//when the array board should be expanded. 
bool corner_flag_set(vec2d& vec)
{
	int row = vec.get_row_len()-2;
	int col = vec.get_col_len()-2;
    for(int i=1; i<row; i++)
    {
		if(	vec[row][i]==1) {
			cout << "Got1 [" << row+2 << "][" << i+1 << "]" << endl;
			return true;
		}
		if (vec[i][col]==1) {
			cout << "Got2 [" << i+1 << "][" << col+2 << "]" << endl;			
			return true;
		}
    }
	
	for(int i=1; i<col; i++)
    {
		//if(	vec[1][i]==1 ) {
		//	cout << "Got3 [" << 1+1 << "][" << i+1 << "]" << endl;
		//	return true;
		//}
		if (vec[col][i]==1) {
			cout << "Got4 [" << col+2 << "][" << i+1 << "]" << endl;
			return true;
		}
    }
    return false;
}

void vec2d::set_vec(vector<int>& v){
	vec=v;
}

//function outside class 
void set_sequence(vec2d& vec, string seq) {
	//Generates a random state 
	int row = vec.get_row_len();
	int col = vec.get_col_len();
	if (seq == "random" || seq == "r") {
		srand(time(NULL));
		for(int j = 0; j < row; j++)
        {
			for (int i = 0; i < col; i++)
				vec[j][i] = rand() % 2;
		}	
	}
	//Generates a glider state 
	else if (seq == "gliders" || seq == "g") {
		if (row >=8 && col >= 8) {
			vec[1][2] = 1;
			vec[2][3] = 1;
			vec[3][1] = 1;
			vec[3][2] = 1;
			vec[3][3] = 1;
		}
		else 
			cout << "\n\nERROR: dimensions must be at least 5 x 5." << endl << endl;
	}
	//Generates a gun state 
	else if (seq == "guns") {
		
	}
}

vector<int> double_vec(vec2d& vec) {
	int new_size = vec.get_row_len() * vec.get_col_len() * FACTOR;
	cout << "now resizing to " << new_size << endl;
	vector<int> v(new_size, 0);
	//v.resize(new_size);
	//vec.set_vec(v);
	return v;
}


#endif
 
