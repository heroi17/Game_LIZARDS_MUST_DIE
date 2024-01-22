#include "PolynomSolve.h"
#include <cmath>
#include <iostream>
using namespace PS;


void PS::output_polynom(double* polynom, int stepen) {
	for (int i = 0; i < stepen + 1; i++) {
		if (polynom[i] < 0) std::cout << " - ";
		else std::cout << " + ";
		std::cout << abs(polynom[i]);
		std::cout << "x^" << stepen - i;
	}
	std::cout << std::endl;
	return void();
}
void PS::output_answer(double* answer, int how_answer) {
	std::cout << "[ ";
	for (int i = 0; i < how_answer - 1; i++) {
		std::cout << 'x' << i + 1 << " = " << answer[i] << ", ";
	}
	std::cout << "x" << how_answer << " = " << answer[how_answer - 1] << " ]";
	std::cout << std::endl;
}

void PS::output_data(double* data, int how_stepen) {
	std::cout << "Data of polynom-----------------------------------" << std::endl;

	double* ykaz = data;
	for (int i = how_stepen; i > 0; i--) {
		std::cout << "answer of polynom          \\V/";
		output_answer(ykaz, how_stepen);
		std::cout << "derivative of last polynom";
		output_polynom(ykaz + how_stepen, how_stepen);
		output_answer(ykaz + how_stepen * 2 + 1, how_stepen);
		std::cout << std::endl;
		ykaz += 2 * how_stepen + 1;
		how_stepen--;
	}
	std::cout << "--------------------------------------------------" << std::endl;
}

void PS::makeproizwpolynom(double* ptr_answer, double* ptr_polynom, int how_stepen) {
	int ptr = 0;
	for (int i = how_stepen; i > 0; i--) {
		ptr_answer[ptr] = ptr_polynom[ptr] * i;
		ptr++;
	}
}
double PS::get_polynom_answer_at(double x, double* ptr_polynom, int how_stepen) {
	double answer = 0;
	if (how_stepen == -1) return 0;
	for (int i = 0; i < how_stepen; i++) {
		answer += ptr_polynom[i];
		answer *= x;
	}answer += ptr_polynom[how_stepen];
	return answer;
}
double PS::find_answer_betwen(double x_start, double x_end, double* ptr_polynom, int how_stepen, double epsilon) {
	double midle;
	if (get_polynom_answer_at(x_end, ptr_polynom, how_stepen) > 0 and x_start < 10e9) {
		while (x_end - x_start > epsilon) {
			midle = (x_end + x_start) / 2;
			if (get_polynom_answer_at(midle, ptr_polynom, how_stepen) < 0) {
				x_start = midle;
			}
			else {
				x_end = midle;
			}
		} return x_start;
	}
	while (x_end - x_start > epsilon and x_start < 10e9) {
		midle = (x_end + x_start) / 2;
		if (get_polynom_answer_at(midle, ptr_polynom, how_stepen) < 0) {
			x_end = midle;
		}
		else {
			x_start = midle;
		}
	} return x_start;
}


int PS::solvepolynom(double* ptr_answer, double* ptr_polynom, int how_stepen, double epsilon) {
	//ptr_polynom has a place in itself for solving the derivative and storing its values and solving it
	//in memory we see this:
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
	// 
	//       ptr_answer - |           | - ptr_polynom
	//                    V           V
	//                   |solutions N|polynom N degree|solutions N-1|poly d N-1|sol N-2|poly N-2|............|sol 1|poly 1|
	//                     A                    A                                A                             A         A
	//                     | - N douuble        | - N+1 double                   | - N-2 double            1 - |         | - 2 double
	// 
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
	// so we should ptr_answer syze set equal to (N+1)^2 <=> (how_stepen+1)^2
	if (how_stepen >= 2) {
		if (ptr_polynom[0] == 0) {
			return solvepolynom(ptr_answer, ptr_polynom + 1, how_stepen - 1, epsilon);
		}
		else {
			int how_answer = 0;
			double* proizw_answer = ptr_polynom + how_stepen + 1;//go further in data to next solutions and polynom;
			double* proizw_polynom = ptr_polynom + 2 * how_stepen;
			makeproizwpolynom(proizw_polynom, ptr_polynom, how_stepen);
			int how_extremum = solvepolynom(proizw_answer, proizw_polynom, how_stepen - 1, epsilon);//get solution proizw
			//check for first extrmum 
			double x_end;
			double x_start;
			if (how_extremum == 0) {
				x_start = -1E20;
				x_end = 1E20;
				if (get_polynom_answer_at(x_start, ptr_polynom, how_stepen) * get_polynom_answer_at(x_end, ptr_polynom, how_stepen) < 0) {
					ptr_answer[how_answer] = find_answer_betwen(x_start, x_end, ptr_polynom, how_stepen, epsilon);
					how_answer++;
				}
			}
			else {//exist more zhen zero extremum


				//find first x
				x_end = proizw_answer[0];
				x_start = x_end - 1E20;
				if (get_polynom_answer_at(x_start, ptr_polynom, how_stepen) * get_polynom_answer_at(x_end, ptr_polynom, how_stepen) <= 0) {
					ptr_answer[how_answer] = find_answer_betwen(x_start, x_end, ptr_polynom, how_stepen, epsilon);
					how_answer++;
				}

				//find x between first and last
				for (int i = 0; i < how_extremum - 1; i++) {
					x_start = proizw_answer[i];
					x_end = proizw_answer[i + 1];
					if (get_polynom_answer_at(x_start, ptr_polynom, how_stepen) * get_polynom_answer_at(x_end, ptr_polynom, how_stepen) <= 0) {
						ptr_answer[how_answer] = find_answer_betwen(x_start, x_end, ptr_polynom, how_stepen, epsilon);
						how_answer++;
					}
				}

				//find last x
				x_start = proizw_answer[how_extremum - 1];
				x_end = x_start + 1E20;
				if (get_polynom_answer_at(x_start, ptr_polynom, how_stepen) * get_polynom_answer_at(x_end, ptr_polynom, how_stepen) <= 0) {
					ptr_answer[how_answer] = find_answer_betwen(x_start, x_end, ptr_polynom, how_stepen, epsilon);
					how_answer++;
				}
			}
			return how_answer;
		}
	}
	else if (how_stepen == 1) {
		if (*ptr_polynom == 0. and ptr_polynom[1] == 0.) {
			*ptr_answer = 1.;
			return 1;
		}
		else if (*ptr_polynom == 0.) {
			return 0;
		}
		else {
			*ptr_answer = -ptr_polynom[1] / ptr_polynom[0];
			return 1;
		}
	}
	return 0;
}




double PS::croot(double x) {
	if (x < 0)
		return -pow(-x, 1.0 / 3.0);
	return pow(x, 1.0 / 3.0);
}

void PS::solve3(double* ptr, double A, double B, double C, double D) {
	if (A == 0) {
		solve2(ptr, B, C, D);
		return void();
	}
	double p = (3.0 * A * C - B * B) / (3.0 * A * A);
	double q = (2.0 * B * B * B - 9.0 * A * B * C + 27.0 * A * A * D) / (27.0 * A * A * A);
	double S = (q * q / 4.0) + (p * p * p / 27.0);
	double F;
	if (q == 0)
		F = PI / 2.0;
	if (q < 0)
		F = atan(-2.0 * sqrt(-S) / q);
	if (q > 0)
		F = atan(-2.0 * sqrt(-S) / q) + PI;
	if (S < 0) {
		ptr[0] = 3;
		ptr[1] = 2.0 * sqrt(-p / 3.0) * cos(F / 3.0) - B / (3.0 * A);
		ptr[2] = 2.0 * sqrt(-p / 3.0) * cos((F / 3.0) + 2.0 * PI / 3.0) - B / (3.0 * A);
		ptr[3] = 2.0 * sqrt(-p / 3.0) * cos((F / 3.0) + 4.0 * PI / 3.0) - B / (3.0 * A);
	}
	if (S == 0) {
		ptr[0] = 2;
		ptr[1] = 2.0 * croot(-q / 2.0) - B / (3.0 * A);
		ptr[2] = -croot(-q / 2.0) - B / (3.0 * A);
	}
	if (S > 0) {
		ptr[0] = 1;
		ptr[1] = croot((-q / 2.0) + sqrt(S)) + croot((-q / 2.0) - sqrt(S)) - B / (3.0 * A);
	}
}

void PS::solve2(double* ptr, double A, double B, double C) {
	if (A == 0) {
		solve1(ptr, B, C);
		return void();
	}
	double Dis = B * B - 4. * A * C;
	if (Dis < 0.) {
		*ptr = 0.;
	}
	else if (Dis > 0.) {
		*ptr = 2.;
		ptr[1] = (-B - sqrt(Dis)) / (2. * A);
		ptr[2] = (-B + sqrt(Dis)) / (2. * A);
	}
	else {
		*ptr = 1;
		ptr[1] = -B / (2. * A);
	}
}

void PS::solve1(double* ptr, double A, double B) {
	if (A == 0. and B == 0.) {
		*ptr = 1.;
		ptr[1] = 0.;
	}
	else if (A == 0.) {
		*ptr = 0.;
	}
	else if (B == 0.) {
		*ptr = 1.;
		ptr[1] = 0.;
	}
	else {
		*ptr = 1.;
		ptr[1] = -B / A;
	}
}



