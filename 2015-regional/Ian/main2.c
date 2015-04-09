// Created on Mon March 30 2015

double seeding_score(double score) {
	return (8 * (score - 0.75));
}
/*
void forward(int speed);

int main()
{
	printf("Hello, World!\n");
	
	forward(100);
	msleep(3000);
	motor(0, 80);
	motor(2, 20);
	msleep(2200);
	forward(100);
	msleep(3000);
	ao();
	
	return 0;
}

void forward(int speed)
{
	motor(0, speed);
	motor(2, speed);
}
*/

/**
double seeding_score(double score);
	
int main() {
	int c;
	double a_plus_b, s, s2, s3, s4;
	
	s = 0.98411016949153;
	s2 = 0.84375;
	s3 = 0.80508474576271;
	s4 = 

	for (c = 1; c < 10000; ++c) {
		a_plus_b = r(s) * c;
		if (a_plus_b - (int) a_plus_b < 0.001) {
			printf("%4i %8.3f %8.3f %8.3f %8.3f\n",
			c, a_plus_b, a_plus_b - c,
			r(s2) * c,
			r(s3) * c);
		}
	}
}
*/
