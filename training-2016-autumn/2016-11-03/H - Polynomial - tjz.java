import java.math.BigInteger;
import java.util.Scanner;

public class Main
{
	static final int maxn = 27;
	static int t, deg;
	static BigInteger[][] poly = new BigInteger[maxn][maxn], c = new BigInteger[maxn][maxn];
	static BigInteger[] fact = new BigInteger[maxn], f = new BigInteger[maxn], g = new BigInteger[maxn];
	static BigInteger ans;
	public static void main(String[] args) {
		fact[0] = poly[0][0] = c[0][0] = BigInteger.ONE;
		for(int i = 1; i < maxn; ++i)
		{
			fact[i] = fact[i - 1].multiply(BigInteger.valueOf(i));
			poly[i][0] = poly[i - 1][0].multiply(BigInteger.valueOf(i - 1));
			c[i][0] = c[i][i] = BigInteger.ONE;
			for(int j = 1; j < i; ++j)
			{
				poly[i][j] = poly[i - 1][j - 1].subtract(poly[i - 1][j].multiply(BigInteger.valueOf(i - 1)));
				c[i][j] = c[i - 1][j - 1].add(c[i - 1][j]);
			}
			poly[i][i] = poly[i - 1][i - 1];
		}
		Scanner cin = new Scanner(System.in);
		int t = cin.nextInt();
		for( ; t > 0; --t)
		{
			deg = cin.nextInt();
			for(int i = 0; i <= deg; ++i)
				f[i] = cin.nextBigInteger();
			for(int i = 0; i <= deg + 1; ++i)
				g[i] = BigInteger.ZERO;
			for(int i = deg; i >= 0; --i)
			{
				if(f[i].compareTo(BigInteger.ZERO) == 0)
						continue;
				BigInteger sei = f[i], delta = fact[deg + 1].divide(BigInteger.valueOf(i + 1));
				for(int j = 0; j <= i + 1; ++j)
					g[j] = g[j].add(sei.multiply(poly[i + 1][j]).multiply(delta));
				for(int j = 0; j <= i; ++j)
					f[j] = f[j].subtract(sei.multiply(poly[i][j]));
			}
			ans = BigInteger.ZERO;
			for(int i = 0; i <= deg + 1; ++i)
			{
				BigInteger sei = BigInteger.ZERO;
				for(int j = i; j <= deg + 1; ++j)
					sei = sei.add(g[j].multiply(c[j][i]));
				sei = sei.abs();
				ans = ans.add(sei.divide(sei.gcd(fact[deg + 1])));
			}
			System.out.println(ans);
		}
		cin.close();
	}
}
