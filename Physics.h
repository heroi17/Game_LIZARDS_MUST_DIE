#pragma once
#include "PhysSimulation.h"
//yeah, i know that my physics architecture is not perfect but it's my second project after 2-3 month of working with c++
// maker of physics engine is "heroi17"






// bugs
// 
// 1) obj sometimes go thru another obj, it's �������� �����
// 
// 
// 2) sometimes moveble obj go thruth static obj
// 
// 
// 
// 
// 
// 


//TODO:
// 
// 
// collision for box obj
// {
//	can add welosity or tp to pbject(maybe ������� �������� ��� �������� � ��������� �������� ���������� ��� ��� ����: ������� ����� updater_obj � ������� ��� ����� ���� 
//	cimulation room ����� ��������� �������� � ������ �������� ���������� �� ������� ������� ��������� ���� �������� � �������� ��������� ����������� ������ updater obj
// 
//	physicc simulationCicle: 
//	
//	           O------O---UpdateOneTic() -----> �������� � object � ��� ��������� ������
//	   		   A	  |
//             |	  |
//			   O------O---update_chanje_settings_of_obj()-------� ����� �� ���� updater_obj ��������� ��������� � object �� ����� ����� �� ����� updater_obj
//
// 
// 
//	update_chanje_settings_of_obj() - is func wich we should add
// 
//	if we want to change parameters of obj ->>> we need to change parameter of updater_obj and after nearest update_one_tic program will update real parameters of object
// }
// 
//
//