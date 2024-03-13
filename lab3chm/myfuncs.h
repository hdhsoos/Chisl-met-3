#ifndef MYFUNCS_H
#define MYFUNCS_H

bool checkStrIsNumeric(std::string const& tempStr);
long double convertStrToNumber(std::string convertStr);

void printTask();
void printDash();
void printTable();

void MenuForChoices();
char getCase();

long double getEpsilonDelta(const int& epsilon_delta);
void reselectEpsilonDeltaValue(long double& f_epsilon_delta, const int& epsilon_delta);
double getComponentOfInitApprox();
bool getInitialApproximation(long double f_init_approx_mass[], bool& f_flag_init_approx, const int& method);

void simpleIterationMethod(long double& f_epsilon, long double& f_delta, long double f_init_approx_mass[], bool& f_flag_init_approx, const int& user_mode);
void NewtonsMethod(long double& f_epsilon, long double& f_delta, long double f_init_approx_mass[], bool& f_flag_init_approx, const int& user_mode);
void modifiedNewtonsMethod(long double& f_epsilon, long double& f_delta, long double f_init_approx_mass[], bool& f_flag_init_approx, const int& user_mode);
#endif /* MYFUNCS_H_ */