#include <iostream>
#include <cstdlib>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <ctime>
#define SIZE 25000

using namespace std;

class Point{
	public:
	int x;
	int y;
	int z;
	Point( int a, int b, int c){
		this->x = a;
		this->y = b;
		this->z = c;
	}
	Point(){
		x = 0;
		y = 0;
		z = 0;
	}
};

int points;
int dist_number = 0; // to calculate number of distance calculations

double dist( Point p1, Point p2){
	dist_number++;
	return sqrt(pow(p1.x-p2.x,2) + pow(p1.y-p2.y,2) + pow(p1.z-p2.z,2));  //3-D distance
}

bool compareX(Point const & a, Point const & b){ //for sort function
	return a.x < b.x;
}
bool compareY(Point const & a, Point const & b){ //for sort function
	return a.y < b.y;
}

double Closest_Pair_Brute( Point last[],int size_p){ //for last 3 or less points
	double min = 100000;
	for( int i = 0; i < size_p; i++){ // brute force
		for( int j = i + 1; j < size_p; j++){
			if ( dist(last[i],last[j]) < min) min = dist(last[i],last[j]);
		}
	}
	return min;
}

double Closest_Pair_Rec( Point px[], int size_p){
	int size = size_p;
	Point qx[size / 2]; // qx and aq
	Point rx[size - (size / 2)]; // rx and ry
	int i,s_points = 0,x_max,j; //iterators , x star, split numbers
	double q0_q1 = 0,r0_r1 = 0,min_s = 100000;  // min of L, min of qx , min of rx
	double teta = 0;
	Point S[size];
	
	if( size <= 3) return Closest_Pair_Brute(px,size);
	
	
	for ( i = 0; i < size / 2; i++) qx[i] = px[i];
	j = i;
	for ( i = 0; i < size - (size / 2); i++){
		rx[i] = px[j];
		j++;
	}
	
	q0_q1 = Closest_Pair_Rec(qx,size/2); 
	r0_r1 = Closest_Pair_Rec(rx,size - (size/2));
	
	teta = min(q0_q1, r0_r1); //min of qx and rx
	x_max = qx[(size /2) - 1].x; // x star, x of L
	
	for( i = 0; i < size / 2; i++){
		if ( abs(x_max - qx[i].x)<= teta){ // if in the scope add to splits
			S[s_points] = qx[i];
			s_points++;
		}
	}
	for ( i = 0; i < size - (size / 2); i++){
		if( abs(x_max - rx[i].x) <= teta){ // if in the scope add to splits
			S[s_points] = rx[i];
			s_points++;
		}
	}
	sort(S,S+s_points,compareY); // sort Splits according to Y axis
	for ( i = 0; i < s_points; i++){
		for ( j = 1; j < 16 && i + j < s_points; j++){ //compare with next 15
			if ( dist(S[i],S[i + j]) < min_s){
				min_s = dist(S[i],S[i + j]);
				}
		}
	}
	
	if ( min_s < teta) return min_s;
	else if ( q0_q1 < r0_r1) return q0_q1;
	else return r0_r1;
}

double Closest_Pair( Point P_first[]){
	int size = points;
	Point p[size];
	int  i;
	sort(P_first,P_first+size,compareX); //constract px and py
	
	return Closest_Pair_Rec(P_first,size);
}

int main(){
	int current = 0;
	int x,y,z;
	bool opened = true;
	clock_t clock1,clock2;
	ifstream input ("data25000.txt");
	if (input.fail()){
		cout << "File could not open!!";
		opened =false;
	}
	input >> points;
	Point P_input[points];
	if(opened){
		for( int i = 1; i <= 3 * points; i++){
			if ( i % 3 == 1) input >> x;
			if ( i % 3 == 2) input >> y;
			if ( i % 3 == 0){
				input >> z;
				Point temp(x,y,z);
				//cout << temp.x << " " <<temp.y << " " <<temp.z << endl;
				P_input[current] = temp;
				current++;
			}
		}
	}
	clock1 = clock();
	double result = Closest_Pair(P_input);
	clock2 = clock();
	cout << "Time:" << ((double)clock2-clock1) / CLOCKS_PER_SEC << " s" << endl;
	cout << "Closest Distance:"<< result << endl;
	cout << "Number of Distance Calculations:"<< dist_number;
	
}
