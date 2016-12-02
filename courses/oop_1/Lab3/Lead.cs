namespace Lab3 {
    public abstract class Lead : Employee, IManageable {

        public Lead(string name, string surname) : base(name, surname) { }

        public int MoneyPaidToTeam { get; set; }

        public abstract void HireTeam();

        public abstract void SetTask(int amount);

    }
}
