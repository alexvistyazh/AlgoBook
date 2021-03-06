class ConvexHullTrick {
private:
	struct Line {
		long long a, b;

		long long get(long long x) const {
			return a * x + b;
		}
	};

	vector<Line> hull;

	bool isBad(vector<Line>::iterator curr) {
		vector<Line>::iterator prev = curr, next = curr;
		--prev, ++next;
		const Line& p = *prev, c = *curr, n = *next;
		return (c.b - n.b) * (long double)(c.a - p.a)
			<= (p.b - c.b) * (long double)(n.a - c.a);
	}

public:
	ConvexHullTrick() : hull() {}

	void add(long long a, long long b) {
		hull.push_back((Line){a, b});
		while (hull.size() > 2 && isBad(hull.end() - 2))
			hull.erase(hull.end() - 2);
	}

	long long get(long long x) const {
		int l = 0, r = int(hull.size()) - 1;
		while (l < r) {
			int m = (l + r) / 2;
			if (hull[m].get(x) <= hull[m + 1].get(x))
				l = m + 1;
			else
				r = m;
		}
		return hull[l].get(x);
	}

	long long fastGet(long long x) {
		static int it = 0;
		it = min(it, int(hull.size()) - 1);
		while (it + 1 < hull.size()) {
			if (hull[it].get(x) > hull[it + 1].get(x))
				break;
			it++;
		}
		while (it > 0) {
			if (hull[it].get(x) > hull[it - 1].get(x))
				break;
			it--;
		}
		return hull[it].get(x);
	}

	void clear() {
		hull.clear();
	}
};
