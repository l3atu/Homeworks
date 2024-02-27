
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;


public class Main {
    public static void main(String[] args) {
        Map<String, Handball> teams = new HashMap<>();
        Map<String, Icehockey> teams2 = new HashMap<>();
        
        String[] fixtures=Input.readFile(args[0], true, true);
        for (String fixture : fixtures) {
            String sport = fixture.split("\t")[0];
            String team1 = fixture.split("\t")[1];
            String team2 = fixture.split("\t")[2];
            int score1 = Integer.parseInt(fixture.split("\t")[3].split(":")[0]);
            int score2 = Integer.parseInt(fixture.split("\t")[3].split(":")[1]);
            if (sport.equals("H")) {
    
                teams.computeIfAbsent(team1, Handball::new);
                teams.computeIfAbsent(team2, Handball::new);
                
                Sports h1 = teams.get(team1);
                Sports h2 = teams.get(team2);
                
                h1.calculatePoint(score1, score2);
                h2.calculatePoint(score2, score1);
            }
            else if (sport.equals("I")) {
                teams2.computeIfAbsent(team1, Icehockey::new);
                teams2.computeIfAbsent(team2, Icehockey::new);
                
                Sports I1 = teams2.get(team1);
                Sports I2 = teams2.get(team2);
                
                I1.calculatePoint(score1, score2);
                I2.calculatePoint(score2, score1);
            }
        }
        List<Handball> sortedTeams = teams.values().stream()
                .sorted(Comparator.comparingInt(Handball::getPoints).reversed()
                        .thenComparing(Comparator.comparingInt(Handball::calculatedifference).reversed()))
                .collect(Collectors.toList());
        
        
        for(int i=0; i< sortedTeams.size();i++){
            Output.writeToFile("handball.txt", (i+1)+".\t"+sortedTeams.get(i).getTeam()
                    +"\t"+sortedTeams.get(i).getTotalGame()+"\t"
                    +sortedTeams.get(i).getWins()+"\t"
                    +sortedTeams.get(i).getEven()+"\t"
                    +sortedTeams.get(i).getLoses()+"\t"
                    +sortedTeams.get(i).getGolsfor()+":"+sortedTeams.get(i).getGolsagainst()+"\t"
                    +sortedTeams.get(i).getPoints(), true, true);
        }
        
        List<Icehockey> sortedTeams2 = teams2.values().stream()
                .sorted(Comparator.comparingInt(Icehockey::getPoints).reversed()
                        .thenComparing(Comparator.comparingInt(Icehockey::calculatedifference).reversed()))
                .collect(Collectors.toList());
        
        
        for(int i=0; i< sortedTeams2.size();i++){
            Output.writeToFile("icehockey.txt", (i+1)+".\t"+sortedTeams2.get(i).getTeam()
                    +"\t"+sortedTeams2.get(i).getTotalGame()+"\t"
                    +sortedTeams2.get(i).getWins()+"\t"
                    +sortedTeams2.get(i).getEven()+"\t"
                    +sortedTeams2.get(i).getLoses()+"\t"
                    +sortedTeams2.get(i).getGolsfor()+":"+sortedTeams2.get(i).getGolsagainst()+"\t"
                    +sortedTeams2.get(i).getPoints(), true, true);
        }
    }
}
