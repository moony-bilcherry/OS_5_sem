@echo off
echo -- List of parameters: %1 %2 %3
echo -- Parameter 1: %1
echo -- Parameter 2: %2
echo -- Parameter 3: %3
set /a eq1 = %1 + %2
set /a eq2 = %1 * %2 
set /a eq3 = %3 / %2 
set /a eq4 = %2 - %1 
set /a eq5 = (%2 - %1) * (%1 - %2)
echo -- %1 + %2 = %eq1%
echo -- %1 * %2 = %eq2% 
echo -- %3 / %2 = %eq3% 
echo -- %2 - %1 = %eq4% 
echo -- (%2 - %1)*(%1 - %2) = %eq5% 