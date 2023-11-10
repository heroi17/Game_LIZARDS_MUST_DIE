#pragma once
namespace PS {
	const double PI = 3.1415926535897932384626433832795028841971;
	/// <summary>
	/// Func uotput in console all information about work of solvepolynom().
	/// Use it after call func solvepolynom().
	/// </summary>
	/// <param name="data"> - Pointer on </param>
	/// <param name="how_stepen"></param>
	void output_data(double* data, int how_stepen);
	void output_polynom(double* polynom, int stepen);
	void output_answer(double* answer, int how_answer);
	/// <summary>
	/// Func calculate derivative of polynom and put it into (double)ptr_answer.
	/// </summary>
	/// <param name="ptr_answer"> - A pointer to the answer</param>
	/// <param name="ptr_polynom"> - A pointer to the place where to put the values of the derivative of the polynomial.</param>
	/// <param name="how_stepen"> -  The degree of this polynomial.</param>
	void makeproizwpolynom(double* ptr_answer, double* ptr_polynom, int how_stepen);
	/// <summary>
	/// Func put x in polynom and return f(x) where f - polynom.
	/// </summary>
	/// <param name="x"> - An argument for finding function values.</param>
	/// <param name="ptr_polynom"> - A pointer to the polynomial.</param>
	/// <param name="how_stepen"> -  The degree of this polynomial.</param>
	/// <returns> (double)polynom(x)</returns>
	double get_polynom_answer_at(double x, double* ptr_polynom, int how_stepen);
	/// <summary>
	/// Searches for the approximate root of the polynomial at the intersection with y = 0. It works correctly provided that the product of the values of the functions at the ends is less than or equal to zero. 
	/// </summary>
	/// <param name="x_start"> - The beginning of the segment on which the root is being searched.</param>
	/// <param name="x_end"> - End of this segment.</param>
	/// <param name="ptr_polynom"> - A pointer to the polynomial in which we are looking for roots.</param>
	/// <param name="how_stepen"> - The degree of this polynomial.</param>
	/// <param name="epsilon"> - How much the answer may differ from the real one.</param>
	/// <returns> (double)One of roots in segment [x_start, x_end] of polynom.</returns>
	double find_answer_betwen(double x_start, double x_end, double* ptr_polynom, int how_stepen, double epsilon);
	/// <summary>
	/// (work incorrect for answer where polynom have 2 or more intersect answer, exemple(x*x-2x + 1))
	/// Func solve polynom of any dagree ~O(degre^2).
	/// Func put double solutions into ptr_answer[0->solutions-1].
	/// ptr_answer lenth should be >= then how_stepen*(how_stepen+1)/2. it's for optimisation.
	/// </summary>
	/// <param name="ptr_answer">:  Pointer, which lenth >=  how_stepen*(how_stepen+1)/2 </param>
	/// <param name="ptr_polynom">: Pointer on polynom ptr_polynom[0] for coef which degree = how_stepen; [1] -> how_stepen -1;...</param>
	/// <param name="how_stepen">:  equal to degree of polynom</param>
	/// <param name="epsilon">:     accuracy of the solution</param>
	/// <returns>(int) How many solutions polynom have. </returns>
	int solvepolynom(double* ptr_answer, double* ptr_polynom, int how_stepen, double epsilon = 1E-10);
	/// <summary>
	/// Solves a polynomial of the 4rd degree in real.
	/// Put solves in double massive, ptr[0] = how many valid solutions. ptr[1-4] - solves.
	/// Ptr syze=4.
	/// </summary>
	/// <param name="ptr">: pointer on solution lst.</param>
	/// <param name="A">: The coefficient at the 4rd degree.</param>
	/// <param name="B">: The coefficient at the 3rd degree.</param>
	/// <param name="C">: The coefficient at the 2rd degree.</param>
	/// <param name="D">: The coefficient at the 1rd degree.</param>
	/// <param name="E">: The free coefficient.</param>
	/// <returns>Void.</returns>
	void solve4(double* ptr, double A, double B, double C, double D, double E);
	/// <summary>
	/// Solves a polynomial of the 3rd degree in real.
	/// Put solves in double massive, ptr[0] = how many valid solutions. ptr[1-3] - solves.
	/// Ptr syze=4.
	/// </summary>
	/// <param name="ptr">: pointer on solution lst.</param>
	/// <param name="A">: The coefficient at the 3rd degree.</param>
	/// <param name="B">: The coefficient at the 2rd degree.</param>
	/// <param name="C">: The coefficient at the 1rd degree.</param>
	/// <param name="D">: The free coefficient.</param>
	/// <returns>Void.</returns>
	void solve3(double* ptr, double A, double B, double C, double D);
	/// <summary>
	/// Solves a polynomial of the 2rd degree in real.
	/// Put solves in double massive, ptr[0] = how many valid solutions. ptr[1-2] - solves.
	/// Ptr syze=3.
	/// </summary>
	/// <param name="ptr">: pointer on solution lst.</param>
	/// <param name="A">: The coefficient at the 2rd degree.</param>
	/// <param name="B">: The coefficient at the 1rd degree.</param>
	/// <param name="C">: The free coefficient.</param>
	/// <returns>Void.</returns>
	void solve2(double* ptr, double A, double B, double C);
	/// <summary>
	/// Solves a polynomial of the 2rd degree in real.
	/// Put solves in double massive, ptr[0] = how many valid solutions. ptr[1] - solve.
	/// Ptr syze=1.
	/// </summary>
	/// <param name="ptr">: pointer on solution lst.</param>
	/// <param name="A">: The coefficient at the 2rd degree.</param>
	/// <param name="B">: The free coefficient.</param>
	/// <returns>Void.</returns>
	void solve1(double* ptr, double A, double B);
	/// <summary>
	/// calculate 3rd root from x
	/// </summary>
	double croot(double x);
}