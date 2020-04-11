#include<iostream>
#include<vector>

using namespace std;
void BotClean() {
	vector<vector<int>> dp(2); //dirty position on the grid
	vector<vector<char>> grid(5);
	cout << "GRID: " << endl;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++)
		{
			cout << "# ";
			grid[i].push_back('#');
		}
		cout << endl;
	}
	int r, c, n1, n2, count = 0;
	cout << "enter r and c" << endl;
	cin >> r >> c; //the grid size is fixed at 5*5
	if (r < 0 || r>4 || c < 0 || c>4)
		cout << "Invalid Input." << endl;
	else {
		cout << "Enter the dirty spots on the grid (press -1 to exit): " << endl;
		cin >> n1 >> n2;
		while (n1 >= 0 && n1 < 5) {
			dp[0].push_back(n1);
			dp[1].push_back(n2);
			count++;
			cin >> n1 >> n2;
		}
		cout << "GRID:" << endl;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (i == r && j == c)
					grid[i][j] = 'b';
				for (int k = 0; k < count; k++) {
					if (dp[0][k] == i && dp[1][k] == j)
						grid[i][j] = 'd';
				}
			}
		}
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				cout << grid[i][j] << ' ';
			}
			cout << endl;
		}

	}
	int cr = r, cc = c;
	while (count != 0) {
		if (grid[cr][cc] == 'd') {
			cout << "CLEAN" << endl;
			grid[cr][cc] = '#';
			for (int i = 0; i < dp[0].size(); i++) {
				if (dp[0][i] == cr && dp[1][i] == cc) {
					dp[0].erase(dp[0].begin() + i);
					dp[1].erase(dp[1].begin() + i);
				}
			}
			count--;
		}
		if (cr != 4 && grid[cr + 1][cc] == 'd') {
			cout << "DOWN" << endl;
			cr++;
		}
		else if (cr != 0 && grid[cr - 1][cc] == 'd') {
			cout << "UP" << endl;
			cr--;
		}
		else if (cc != 4 && grid[cr][cc + 1] == 'd') {
			cout << "RIGHT" << endl;
			cc++;
		}
		else if (cc != 0 && grid[cr][cc - 1] == 'd') {
			cout << "LEFT" << endl;
			cc--;
		}
		else {
			//no dirty spots in the immediate vicinity of bot.
			if (cr != 4 && cc != 4 && grid[cr + 1][cc + 1] == 'd') {
				cout << "DOWN" << endl;
				cr++;
			}
			else if (cr != 4 && cc != 0 && grid[cr + 1][cc - 1] == 'd') {
				cout << "DOWN" << endl;
				cr++;
			}
			else if (cc != 4 && cr != 0 && grid[cr - 1][cc + 1] == 'd') {
				cout << "UP" << endl;
				cr--;
			}
			else if (cc != 0 && cr != 0 && grid[cr - 1][cc - 1] == 'd') {
				cout << "UP" << endl;
				cr--;
			}
			else {
				//no dirty spot in the larger vicinity of bot.
				//the only thing we can do now is to take the bot to the first stored dirty
				//spot in the bots input vector
				if (!count) break;
				if (cr > dp[0][0]) {
					cout << "UP" << endl;
					cr--;
				}
				else if (cr < dp[0][0]) {
					cout << "DOWN" << endl;
					cr++;
				}
				else {
					if (cc > dp[1][0]) {
						cout << "LEFT" << endl;
						cc--;
					}
					else if (cc < dp[1][0]) {
						cout << "RIGHT" << endl;
						cc++;
					}
				}	
			}
		}
	}

}
int main() {
	BotClean();
	return 0;
}
