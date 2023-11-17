#pragma once
#include "PhysSimulation.h"
//yeah, i know that my physics architecture is not perfect but it's my second project after 2-3 month of working with c++
// maker of physics engine is "heroi17"






// bugs
// 
// 1) obj sometimes go thru another obj, it's довольно редко
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
//	can add welosity or tp to pbject(maybe создать оболочку для обжектов и обнавлять значение переменных для них типо: создать класс updater_obj и сделать так чтобы цикл 
//	cimulation room после обработки коллизий в каждой итерации проходился по массиву ивентов изменения этих обьектов и применял изменения сохраненные внутри updater obj
// 
//	physicc simulationCicle: 
//	
//	           O------O---UpdateOneTic() -----> работает с object и его реальными полями
//	   		   A	  |
//             |	  |
//			   O------O---update_chanje_settings_of_obj()-------в цикле по всем updater_obj применяем изменения к object он будет одним из полей updater_obj
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