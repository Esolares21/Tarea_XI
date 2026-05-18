public class Estudiante {
    private int studentId;
    private String fullName;
    private String career;
    private int semesterGua;
    private double skillScore;

    public Estudiante(int studentId, String fullName, String career, int semesterGua, double skillScore) {
        this.studentId = studentId;
        this.fullName = fullName;
        this.career = career;
        this.semesterGua = semesterGua;
        this.skillScore = skillScore;
    }

    public int getStudentId() {
        return studentId;
    }

    @Override
    public String toString() {
        return "ID: " + studentId +
                "\nNombre: " + fullName +
                "\nCarrera: " + career +
                "\nSemestre: " + semesterGua +
                "\nNota de Habilidad: " + skillScore;
    }
}