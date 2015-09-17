#include "Vec3.h"

int main(int argc, char** argv)
{
	Vec3<int> vz;

	vz.SetPosition(8);

	printf("%d", vz.GetPosition());

	getchar();

	return 0;
}