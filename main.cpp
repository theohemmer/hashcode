#include <iostream>
#include <string>
#include <cstring>
#include <string.h>

char **workers_name = NULL;
char **comp_name = NULL;
char **projects_name = NULL;

typedef struct comp_s {
    unsigned int name;
    unsigned int level;
} comp_t;

typedef struct wokers_s {
    unsigned int name;
    unsigned int number_of_comp;
    comp_t *comps;
} workers_t;

typedef struct projects_s {
    unsigned int name;
    unsigned int days;
    unsigned int score;
    unsigned int max_day;
    unsigned int number_of_roles;
    comp_s *roles;
} projects_t;

void init_workers(workers_t *workers, int n)
{
    for (size_t i = 0; i < n; i++) {
        std::string name;
        int competances;
        std::cin >> name;
        std::cin >> competances;
        workers_name[i] = strdup((char *) name.c_str());
        workers[i].name = i;
        workers[i].number_of_comp = competances;
        workers[i].comps = (comp_t *) malloc(sizeof(comp_t *) * (competances + 1));
        for (size_t o = 0; o < competances; o++) {
            std::string a_comp_name;
            int comp_level;
            std::cin >> a_comp_name;
            std::cin >> comp_level;
            size_t p = 0;
            for (; comp_name && comp_name[p]; p++)
                if (strcmp(a_comp_name.c_str(), (const char *) comp_name[p]) == 0)
                    break;
            if (!comp_name || !comp_name[p]) {
                comp_name = (char **) realloc(comp_name, sizeof(char **) * (p + 2));
                comp_name[p] = strdup((char *) a_comp_name.c_str());
                comp_name[p + 1] = NULL;
            }
            workers[i].comps[o].level = comp_level;
            workers[i].comps[o].name = p;
        }
    }
}

void init_projects(projects_t *projects, int n)
{
    for (size_t i = 0; i < n; i++) {
        std::string name;
        int score;
        int max_day;
        int roles;
        int days;
        std::cin >> name;
        std::cin >> days;
        std::cin >> score;
        std::cin >> max_day;
        std::cin >> roles;
        projects_name[i] = strdup((char *) name.c_str());
        projects[i].name = i;
        projects[i].score = score;
        projects[i].max_day = max_day;
        projects[i].number_of_roles = roles;
        projects[i].days = days;
        projects[i].roles = (comp_t *) malloc(sizeof(comp_t *) * (roles + 1));
        for (size_t o = 0; o < roles; o++) {
            std::string a_comp_name;
            int required_level;
            std::cin >> a_comp_name;
            std::cin >> required_level;
            size_t p = 0;
            for (; comp_name && comp_name[p]; p++)
                if (strcmp(a_comp_name.c_str(), (const char *) comp_name[p]) == 0)
                    break;
            if (!comp_name || !comp_name[p]) {
                comp_name = (char **) realloc(comp_name, sizeof(char **) * (p + 2));
                comp_name[p] = strdup((char *) a_comp_name.c_str());
                comp_name[p + 1] = NULL;
            }
            projects[i].roles[o].level = required_level;
            projects[i].roles[o].name = p;
        }
    }
}

int main(void)
{
    workers_t *workers;
    projects_t *projects;
    int number_of_contributors;
    int number_of_projects;
    std::cin >> number_of_contributors;
    std::cin >> number_of_projects;

    workers = (workers_t *) malloc(sizeof(workers_t) * (number_of_contributors + 1));
    projects = (projects_t *) malloc(sizeof(projects_t) * (number_of_projects + 1));
    workers_name = (char **) malloc(sizeof(char **) * (number_of_contributors + 1));
    projects_name = (char **) malloc(sizeof(char **) * (number_of_projects + 1));
    init_workers(workers, number_of_contributors);
    init_projects(projects, number_of_projects);

    for (size_t i = 0; i < number_of_contributors; i++) {
        printf("CONTRIBUTORS:\n");
        printf(" - %s %d:\n", workers_name[workers[i].name], workers[i].name);
        for (size_t o = 0; o < workers[i].number_of_comp; o++) {
            printf("  + %s %d %d\n", comp_name[workers[i].comps[o].name], workers[i].comps[o].level, workers[i].comps[o].name);
        }
    }
    for (size_t i = 0; i < number_of_projects; i++) {
        printf("PROJECTS:\n");
        printf(" - %s %d (Days: %d) (Score: %d) (Max: %d):\n", projects_name[projects[i].name], projects[i].name, projects[i].days, projects[i].score, projects[i].max_day);
        for (size_t o = 0; o < projects[i].number_of_roles; o++) {
            printf("  + %s %d %d\n", comp_name[projects[i].roles[o].name], projects[i].roles[o].level, projects[i].roles[o].name);
        }
    }
}