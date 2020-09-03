
public class Person {
	protected String name;
	protected String gender;
	protected short age;
	
	public Person(String name, String gender, short age) {
		this.name = name.equals("Victor") ? "Viktor" : name;
		this.gender = gender;
		this.age = age;
	}

	public String toString() {
		return String.format("%s[gen: %s, age: %d]", name, gender, age);
	}
}
