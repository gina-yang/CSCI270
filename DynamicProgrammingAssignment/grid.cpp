/*
	CSCI 270 Fall 2018
	Programming Assignment
	Name   : Gina Yang
	Email  : ginayang@usc.edu
	USC ID : 3922590021
*/

// Compile using command: g++ -g -Wall -std=c++11 grid.cpp -o grid
// Run using command: ./grid

// Sources used: https://algorithms.tutorialhorizon.com/dynamic-programming-minimum-cost-path-problem/

#include <iostream>
#include <vector>
#include <string>
#include <climits>
using namespace std;

int solve(int N, vector<vector<string> > G);

struct Tile{
	// Tile properties - we need to track these for each tile because they can carry over to the next
	int value; 	// The value of a tile represents the minimum amount of health needed to finish progressing after that point
	int isD; // Double next healing effect
	int isP; // Prevent next damage effect
	int isDP; // Both D and P

	void setTileHealth(int P, int D, int DP, int val){
		// Set the tile properties
		value = val;
		isD = D;
		isP = P;
		isDP = DP;
	}
};

int solve(int N, vector<vector<string> > G) {
/*
	Please complete this function.
	N: Number of rows / columns of the grid.
	G: A 2d vector (N*N) indicating the grid.
		G[0][0] is the top left corner
		G[N-1][N-1] is the bottom right corner
	Return: the minimum life Brain needs to complete his task.
*/

	// Create an array with a row and column of padding (so we don't have to fudge with edge cases for the last row and column,
	// which will have nothing to their right/bottom)
	Tile** tile = new Tile*[N + 1];

	// Initialize values in the array with "infinity" (max values)
	for( int i = 0; i <= N; i++ ){
		tile[i] = new Tile[N + 1];
		for( int j = 0; j <= N; j++ ){
			tile[i][j].setTileHealth(INT_MAX, INT_MAX, INT_MAX, INT_MAX);
		}
	}

	// Brian needs to finish with one health - these are the tiles flanking tile[N-1][N-1] (bottom right corner)
	// When he is at one of these tiles, he should have one health 
	tile[N - 1][N].setTileHealth(1,1,1,1);
	tile[N][N - 1].setTileHealth(1,1,1,1);

	// Iterate through (starting from the bottom right) to fill the tile properties for each entry. We will end at the 
	// top left corner, which will hold the value we return (minimum health needed to traverse the input array)
	for( int i = N - 1; i >= 0; i-- ){
		for( int j = N - 1; j >= 0; j-- ){
			// When we fill in our "table,"" the two tiles that matter are the tile below (i+1, j) and the tile to the right (i, j+1) 
			// This is because Brian can only move in two directions--right and down
			// We take the minimum of these to set the properties of the tile in question
			if( G[i][j] == "P"){
				tile[i][j].setTileHealth(min(tile[i+1][j].isP, tile[i][j+1].isP),
										 min(tile[i+1][j].isDP, tile[i][j+1].isDP), 
										 min(tile[i+1][j].isDP, tile[i][j+1].isDP),
										 min(tile[i+1][j].isP, tile[i][j+1].isP));
			}
			else if( G[i][j] == "D" ){
				tile[i][j].setTileHealth(min(tile[i+1][j].isDP, tile[i][j+1].isDP),
										 min(tile[i+1][j].isD, tile[i][j+1].isD),
										 min(tile[i+1][j].isDP, tile[i][j+1].isDP), 
										 min(tile[i+1][j].isD, tile[i][j+1].isD));
			}
			else{ // Integer value - guard or heal
				tile[i][j].value = max(1, min(tile[i+1][j].value, tile[i][j+1].value) - stoi(G[i][j]));

				if( stoi(G[i][j]) < 0 ){ // Negative value indicates guard
					tile[i][j].isP = max(1, min(tile[i+1][j].value, tile[i][j+1].value));
					tile[i][j].isD = max(1, min(tile[i+1][j].isD, tile[i][j+1].isD) - stoi(G[i][j]));
					tile[i][j].isDP = max(1, min(tile[i+1][j].isD, tile[i][j+1].isD));
				}

				else if( stoi(G[i][j]) >= 0 ){ // Positive value indicates healing
					tile[i][j].isP = max(1, min(tile[i+1][j].isP, tile[i][j+1].isP - stoi(G[i][j])));
					tile[i][j].isD = max(1, min(tile[i+1][j].value, tile[i][j+1].value) - 2*stoi(G[i][j]));
					tile[i][j].isDP = max(1, min(tile[i+1][j].isP, tile[i][j+1].isP) - 2*stoi(G[i][j]));
				}
			}
		}
	}
	// The minimum (optimum) starting value will be located at the leftmost top tile. return it
	return tile[0][0].value;
}

//	The main function reads the input and outputs your answer.
//	Please do not modify it. (Assume the input is well-formed;
//	You don't need to do any error-check)
int main(int argc, char **argv) {
	int N;
	vector<vector<string> > G;
	cin >> N;
	G.resize(N);
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			string tmp;
			cin >> tmp;
			G[i].push_back(tmp);
		}
	}
	cout << solve(N, G) << endl;
	return 0;
}