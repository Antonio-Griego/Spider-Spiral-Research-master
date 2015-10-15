/*****
 * This file contains the Algorithm for DSA (Determinstic Spider Algorithm)
 * This file is extension of the matlab version created by Matthew Fricke and Linh Tran
 * on 8/11/15. This version interprets patterns for multiple robots preforming
 * the DSA algorithm. 
 * Authors: Linh Tran and Matthew Fricke
 * Date: 09/29/15
 *****/

#include <vector>
#include <iostream>
using namespace std;
//Declaring functions
void generatePattern(int N_circuits, int N_robots);
int calcDistanceToTravel(int i_robot, int i_circuit, int N_robots, char direction);
void writePatternToFile(vector<char>&, int N_robots);
void addDirectionToPattern(char direction);
void printPath(vector<char>&);

void generatePattern(int N_circuits, int N_robots)
{
	//initialize paths for the robots
	vector<vector< char> > paths;

	// for (int i = 0; i<N_robots; i++)
	// {
	// 	vector<char> ith_path;
	// 	for (int j = 0; j < 20; j++)
	// 	{
	// 		ith_path.push_back('N');
	// 		cout << i;
	// 	}
	// 	paths.push_back(ith_path);	 
	// }
	// cout << "N_circuits" << N_circuits <<endl;
	// cout << "N_robots" << N_robots << endl;
	// cout << "inside generatePattern" << endl;
	vector<char> ith_robot_path; 
	for (int i_robot = 1; i_robot< N_robots; i_robot++)
	{
		// cout << "inside for 1" << endl;
		for (int i_circuit = 0; i_circuit < N_circuits; i_circuit++)
		{
			int n_steps_north = calcDistanceToTravel(i_robot, i_circuit, N_robots, 'N');
			for (int j = 0; j < n_steps_north; j++)
			{
				ith_robot_path.push_back('N');
			}
			
			int n_steps_east = calcDistanceToTravel(i_robot, i_circuit, N_robots, 'E');
			for (int j = 0; j < n_steps_east; j++)
			{
				ith_robot_path.push_back('E');
			}

			int n_steps_south = calcDistanceToTravel(i_robot, i_circuit, N_robots, 'S');
			for (int j = 0; j < n_steps_south; j++)
			{
				ith_robot_path.push_back('S');
			}

			int n_steps_west = calcDistanceToTravel(i_robot, i_circuit, N_robots, 'W');
			for (int j = 0; j < n_steps_west; j++)
			{
				ith_robot_path.push_back('W');
			}
		}
	}
	printPath(ith_robot_path);
	// for (int i = 0; i<N_robots; i++)
	// {
	// 	paths[i].push_back(ith_robot_path);	 
	// }
}

int calcDistanceToTravel(int i_robot, int i_circuit, int N_robots, char direction)
{
	int i = i_robot;
	int j = i_circuit;
	int N = N_robots;
	int n_steps  = 0;

	if (direction == 'N' || direction == 'E')
	{
		if (j == 0)
		{
			n_steps = i;
			return n_steps;
		}
		else if (j == 1)
		{
			n_steps = calcDistanceToTravel(i, j-1, N, direction) + i + N;
			return n_steps;
		}
		else 
		{
			n_steps = calcDistanceToTravel(i, j-1, N, direction) + 2*N;
			return n_steps;
		}
	}

	else if (direction == 'S' || direction == 'W')
	{
		if (j == 0)
		{
			n_steps = calcDistanceToTravel(i, j , N, 'N') + i;
			return n_steps;
		}

		else if (j>0)
		{
			n_steps = calcDistanceToTravel(i, j, N, 'N') + N;
			return n_steps;
		}

		else
		{
			cout << "Error direction" << direction << "is invalid" << endl;
		}

	}
	return 0;
}

void printPath(vector<char>& path)
{
	cout << path.size() << endl;
	for(int i = 0; i<path.size(); i++)
	{ 
		cout << path.at(i) << endl;
	}
}

int main ()
{
	generatePattern(1,2);

	return 0;
}



