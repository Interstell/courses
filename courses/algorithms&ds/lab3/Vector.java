package hashtable;

public class Vector {
	private double x;
	private double y;

	public Vector(double x, double y) {
		this.x = x;
		this.y = y;
	}

	public double getX(){
		return x;
	}
	
	public double getY(){
		return y;
	}
	
	public double getRho() {
		return Math.sqrt(Math.pow(x, 2) + Math.pow(y, 2));
	}

	public int getPhiInDeg() {
		int phi = (int)(Math.atan2(y, x) * (180 / Math.PI));
		if (phi < 0) phi = 180 - phi;
		return phi;
	}

	public double getPhiInRad() {
		return Math.atan2(y, x);
	}

	public void print() {
		System.out.println(getData());
		//System.out.format("Cartesian: (%+2.1f ; %+2.1f) | Polar: (%2.1f ; %3d°)\n", x, y, getRho(), getPhiInDeg());
	}
	
	public String getData(){
		String data = String.format("Cartesian: (%+2.1f ; %+2.1f) | Polar: (%3.1f ; %3d°)", x, y, getRho(), getPhiInDeg());
		return data;
	}

}
