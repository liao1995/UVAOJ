import java.math.BigInteger;
import java.util.Scanner;

public class Main{
	public static void main(String[] args){
		Scanner cin = new Scanner(System.in);
		int n;
		BigInteger p, xk, xn;
		xk = new BigInteger("1");
		xn = new BigInteger("0");
		while (cin.hasNextInt()){
			n = cin.nextInt();
			p = cin.nextBigInteger();
			while (true){
				xn = (p.divide(xk.pow(n-1))
					.add(xk.multiply(BigInteger.valueOf(n-1))))
					.divide(BigInteger.valueOf(n));
				if (xk.compareTo(xn) == 0) break;
				xk = xn;
			}
			System.out.println(xn);
		}
		cin.close();
	}
}
