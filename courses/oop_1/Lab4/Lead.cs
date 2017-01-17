namespace Lab4 {
    public abstract class Lead : Employee, IManageable {

        public Lead(string name, string surname) : base(name, surname) { }

        public int MoneyPaidToTeam { get; set; }

        // #Rule: N2 (Выбирайте имена на подходящем уровне абстракции)

        public abstract void HireTeam();

        // Refactoring #4: Переименование метода (Rename Method)
        // FireAllMembers -> FireTeam
        // SetTask -> SetTeamTask


        public abstract void FireTeam();

        public abstract void SetTeamTask(int amountOfWork);

    }
}
