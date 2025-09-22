int main(int argc, char* argv[]) {
	if (argc == 1) {
		return -1;
	}

	char* pass = "c";

	if (argv[1][0] != pass[0]) {
		return -1;
	}

	return 0;
}
