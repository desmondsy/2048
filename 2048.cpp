#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

void print(vector<vector<int> > vec);
bool move_up(vector<vector<int> > &vec);
bool move_down(vector<vector<int> > &vec);
bool move_left(vector<vector<int> > &vec);
bool move_right(vector<vector<int> > &vec);
bool merge_w(vector<vector<int> > &vec);
bool merge_a(vector<vector<int> > &vec);
bool merge_s(vector<vector<int> > &vec);
bool merge_d(vector<vector<int> > &vec);
void rand_coordinate(vector<vector<int> > &vec);
bool move_merge_w(vector<vector<int> > &vec);
bool move_merge_d(vector<vector<int> > &vec);
bool move_merge_a(vector<vector<int> > &vec);
bool move_merge_s(vector<vector<int> > &vec);
bool no_more_space(vector<vector<int> > vec);
bool no_more_valid_moves(vector<vector<int> > vec);

int score = 0;

// checks if there are any more valid moves on the board
bool no_more_valid_moves(vector<vector<int> > vec) {
	bool r = true;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (vec[i][j] == vec[(i + 1) % 4][j] || vec[i][j] == vec[i][(j + 1)
					% 4]) {

				if ((i + 1) > 3 && vec[i][j] == vec[(i + 1) % 4][j]) {
				} else if ((j + 1) > 3 && vec[i][j] == vec[i][(j + 1) % 4]) {
				} else {
					r = false;
				}
			}
		}
	}
	return r;
}

// if a zero is present, then return false.
bool no_more_space(vector<vector<int> > vec) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (vec[i][j] == 0) {
				return false;
			}
		}
	}
	return true;
}


// output score
void print_score(vector<vector<int> > vec){
	cout << "Score: " << score << endl;
}


// print the board
void print(vector<vector<int> > vec) {
	print_score(vec);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << vec[i][j] << "\t";
		}
		cout << endl << endl;
	}
}


void add_score(int score_added){
	score += score_added;
}


/*for the functions below, change the value of i or j in the for loops to match the operation
 * because both i and j range from 0 to 3, therefore match accordingly. This applies to the merge
 * functions below the move functions below.
 */

// generates a '2' on a valid location on the grid after every action
void rand_coordinate(vector<vector<int> > &vec) {
	vector<int> columns(0, 0);
	vector<int> rows(0, 0);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (vec[i][j] == 0) {
				columns.push_back(i);
				rows.push_back(j);
			}
		}
	}

	int coordinatepair = rand() % columns.size();
	vec[columns[coordinatepair]][rows[coordinatepair]] = 2;
}

// move up
/*
the move merge function executes the move function if a zero is detected.
after movement it will merge if adjacent cells are detected to be equal. If merged,
then move function is called again to move it up to the correct cell
*/
bool move_merge_w(vector<vector<int> > &vec) {
	bool r = false;
	if (move_up(vec)) {
		r = true;
	}
	if (merge_w(vec)) {
		move_up(vec);
		r = true;
	}
	return r;
}

// swap if number above is detected to be a 0
bool move_up(vector<vector<int> > &vec) {

	bool r = false;
	for (int k = 0; k < 4; k++) {
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 3; i++) {
				if (vec[i][j] == 0) {
					//will not enter true loop if vec[i][j]
					// is not 0 and if vec[i+1][j] is 0
					if (vec[i + 1][j] != 0) {
						r = true;
					}
					vec[i][j] = vec[i + 1][j];
					vec[i + 1][j] = 0;
				}
			}
		}
	}
	return r;
}

// the merge function in this case only merges adjacent cells if detected to be equal.
bool merge_w(vector<vector<int> > &vec) {

	bool r = false;
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 3; i++) {
			if (vec[i][j] == vec[i + 1][j]) {
				if (vec[i + 1][j] != 0) {
					r = true;
				}
				vec[i][j] = vec[i + 1][j] + vec[i][j];
				vec[i + 1][j] = 0;
				add_score(vec[i][j]);
			}
		}
	}
	return r;
}


// move right
bool move_merge_d(vector<vector<int> > &vec) {
	bool r = false;
	if (move_right(vec)) {
		r = true;
	}
	if (merge_d(vec)) {
		move_right(vec);
		r = true;
	}
	return r;
}

bool move_right(vector<vector<int> > &vec) {
	bool r = false;
	for (int k = 0; k < 4; k++) {
		for (int j = 3; j > 0; j--) {
			for (int i = 0; i < 4; i++) {
				if (vec[i][j] == 0) {
					if (vec[i][j - 1] != 0) {
						r = true;
					}
					vec[i][j] = vec[i][j - 1];
					vec[i][j - 1] = 0;
				}
			}
		}
	}
	return r;
}

bool merge_d(vector<vector<int> > &vec) {

	bool r = false;
	for (int j = 3; j > 0; j--) {
		for (int i = 0; i < 4; i++) {
			if (vec[i][j] == vec[i][j - 1]) {
				if (vec[i][j - 1] != 0) {
					r = true;
				}
				vec[i][j] = vec[i][j - 1] + vec[i][j];
				vec[i][j - 1] = 0;
				add_score(vec[i][j]);
			}
		}
	}
	return r;
}

// move left
bool move_merge_a(vector<vector<int> > &vec) {
	bool r = false;
	if (move_left(vec)) {
		r = true;
	}
	if (merge_a(vec)) {
		move_left(vec);
		r = true;
	}
	return r;
}

bool move_left(vector<vector<int> > &vec) {

	bool r = false;
	for (int k = 0; k < 4; k++) {
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 4; i++) {
				if (vec[i][j] == 0) {
					if (vec[i][j + 1] != 0) {
						r = true;
					}
					vec[i][j] = vec[i][j + 1];
					vec[i][j + 1] = 0;
				}
			}
		}
	}
	return r;
}

bool merge_a(vector<vector<int> > &vec) {

	bool r = false;
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 4; i++) {
			if (vec[i][j] == vec[i][j + 1]) {
				if (vec[i][j + 1] != 0) {
					r = true;
				}
				vec[i][j] = vec[i][j + 1] + vec[i][j];
				vec[i][j + 1] = 0;
				add_score(vec[i][j]);
			}
		}
	}
	return r;
}


// move down
bool move_merge_s(vector<vector<int> > &vec) {
	bool r = false;
	if (move_down(vec)) {
		r = true;
	}
	if (merge_s(vec)) {
		move_down(vec);
		r = true;
	}
	return r;
}

bool move_down(vector<vector<int> > &vec) {

	bool r = false;
	for (int k = 0; k < 4; k++) {
		for (int j = 0; j < 4; j++) {
			for (int i = 3; i > 0; i--) {
				if (vec[i][j] == 0) {
					if (vec[i - 1][j] != 0) {
						r = true;
					}
					vec[i][j] = vec[i - 1][j];
					vec[i - 1][j] = 0;
				}
			}
		}
	}
	return r;
}

bool merge_s(vector<vector<int> > &vec) {

	bool r = false;
	for (int j = 0; j < 4; j++) {
		for (int i = 3; i > 0; i--) {
			if (vec[i][j] == vec[i - 1][j]) {
				if (vec[i - 1][j] != 0) {
					r = true;
				}
				vec[i][j] = vec[i - 1][j] + vec[i][j];
				vec[i - 1][j] = 0;
				add_score(vec[i][j]);
			}
		}
	}
	return r;
}

int main() {

	srand(time(NULL));
	string wasd;
	int i = 4; //columns
	int j = 4; //rows
	int initialvalue = 0;

	vector < vector<int> > vec;
	vec.resize(j, vector<int> (i, initialvalue));

	vec[3][3] = 2;
	print(vec);

	cin >> wasd;

	while ((wasd == "w" || "a" || "s" || "d") && !(no_more_space(vec)
			&& no_more_valid_moves(vec))) {

		if (wasd == "w") {
			if (move_merge_w(vec)) {
				rand_coordinate(vec);
			}
		}

		if (wasd == "a") {
			if (move_merge_a(vec)) {
				rand_coordinate(vec);
			}
		}

		if (wasd == "s") {
			if (move_merge_s(vec)) {
				rand_coordinate(vec);
			}
		}

		if (wasd == "d") {
			if (move_merge_d(vec)) {
				rand_coordinate(vec);
			}
		}

		print(vec);
		cin >> wasd;
	}

	cout << "YOU LOST!\n";
	return 0;
}



