#include <iostream>
#include <string>
#include <cstring>
#include <string.h>

char **workers_name = NULL;
char **comp_name = NULL;
char **projects_name = NULL;
int max_best_before = 0;

typedef struct comp_s {
    unsigned int name;
    unsigned int level;
} comp_t;

typedef struct wokers_s {
    unsigned int name;
    unsigned int dispo;
    unsigned int in_use;
    unsigned int score;
    unsigned int number_of_comp;
    comp_t *comps;
} workers_t;

typedef struct projects_s {
    unsigned int name;
    unsigned int days;
    unsigned int score;
    unsigned int max_day;
    unsigned int started;
    unsigned int number_of_roles;
    workers_t **workers;
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
        workers[i].in_use = 0;
        workers[i].dispo = 1;
        workers[i].score = 0;
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
        if (max_day > max_best_before)
            max_best_before = max_day;
        projects[i].max_day = max_day;
        projects[i].number_of_roles = roles;
        projects[i].days = days;
        projects[i].started = 0;
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

workers_t **get_dispo_worker(workers_t *workers, comp_t *required, int nw, int nc)
{
    workers_t **dispo = NULL;
    int act_dispo = 0;

    for (size_t i = 0; i < nc; i++) {
        int mentor = 0;
        for (size_t o = 0; o < nw; o++) {
            int score = 0;
            for (size_t p = 0; p < workers[o].number_of_comp; p++) {
                if (workers[o].comps[p].name == required[i].name && workers[o].dispo && workers[o].in_use == 0) {
                    if (workers[o].comps[p].level > required[i].level) {
                        for (size_t x = 0; x < nc && mentor == 0; x++) {
                            if (required[o].name != required[i].name) {
                                for (size_t c = 0; c < workers[o].number_of_comp && mentor == 0; c++) {
                                    if (workers[o].comps[c].level >= required[i].level) {
                                        mentor = 1;
                                        dispo = (workers_t **) realloc(dispo, sizeof(workers_t *) * (act_dispo + 2));
                                        workers[o].dispo = 0;
                                        dispo[act_dispo] = &workers[o];
                                        dispo[act_dispo + 1] = NULL;
                                    }
                                }
                            }
                        }
                        score = 1;
                    }
                    if (workers[o].comps[p].level >= required[i].level) {
                        for (size_t x = 0; x < nc && mentor == 0; x++) {
                            if (required[o].name != required[i].name) {
                                for (size_t c = 0; c < workers[o].number_of_comp && mentor == 0; c++) {
                                    if (workers[o].comps[c].level >= required[i].level) {
                                        mentor = 1;
                                        dispo = (workers_t **) realloc(dispo, sizeof(workers_t *) * (act_dispo + 2));
                                        workers[o].dispo = 0;
                                        dispo[act_dispo] = &workers[o];
                                        dispo[act_dispo + 1] = NULL;
                                    }
                                }
                            }
                        }
                        score = 2;
                    }
                    if (workers[o].comps[p].level >= required[i].level - 1)
                        score = 3;
                }
            }
            workers[o].score = score;
        }
        int last_act_dispo = act_dispo;
        if (mentor != 0) {
            for (size_t o = 0; o < nw; o++) {
                if (workers[o].score == 3) {
                    dispo = (workers_t **) realloc(dispo, sizeof(workers_t *) * (act_dispo + 2));
                    workers[o].dispo = 0;
                    dispo[act_dispo] = &workers[o];
                    dispo[act_dispo + 1] = NULL;
                    break;
                }
            }
            if (act_dispo != last_act_dispo) {
                for (size_t o = 0; o < nw; o++) {
                    if (workers[o].score == 2) {
                        dispo = (workers_t **) realloc(dispo, sizeof(workers_t *) * (act_dispo + 2));
                        workers[o].dispo = 0;
                        dispo[act_dispo] = &workers[o];
                        dispo[act_dispo + 1] = NULL;
                        break;
                    }
                }
                if (act_dispo != last_act_dispo) {
                    for (size_t o = 0; o < nw; o++) {
                        if (workers[o].score == 1) {
                            dispo = (workers_t **) realloc(dispo, sizeof(workers_t *) * (act_dispo + 2));
                            workers[o].dispo = 0;
                            dispo[act_dispo] = &workers[o];
                            dispo[act_dispo + 1] = NULL;
                            break;
                        }
                    }
                }
            }
        }
        else {
            for (size_t o = 0; o < nw; o++) {
                if (workers[o].score == 2) {
                    dispo = (workers_t **) realloc(dispo, sizeof(workers_t *) * (act_dispo + 2));
                    workers[o].dispo = 0;
                    dispo[act_dispo] = &workers[o];
                    dispo[act_dispo + 1] = NULL;
                    break;
                }
            }
            if (act_dispo != last_act_dispo) {
                for (size_t o = 0; o < nw; o++) {
                    if (workers[o].score == 1) {
                        dispo = (workers_t **) realloc(dispo, sizeof(workers_t *) * (act_dispo + 2));
                        workers[o].dispo = 0;
                        dispo[act_dispo] = &workers[o];
                        dispo[act_dispo + 1] = NULL;
                        break;
                    }
                }
            }
        }
    }

    return dispo;
}

projects_t **get_dispo_projects(workers_t *workers, projects_t *projects, int nw, int np, int day)
{
    projects_t **dispo = NULL;
    size_t act_dispo = 0;

    for (size_t i = 0; i < np; i++) {
        if (projects[i].started == 0 && projects[i].max_day < day) {
            workers_t **dispo_w = get_dispo_worker(workers, projects[i].roles, nw, projects[i].number_of_roles);
            size_t size = 0;
            for (size = 0; dispo_w && dispo_w[size]; size++);
            if (size >= projects[i].number_of_roles) {
                dispo = (projects_t **) realloc(dispo, sizeof(projects_t *) * (act_dispo + 2));
                dispo[act_dispo] = &projects[i];
                dispo[act_dispo + 1] = NULL;
            }
        }
    }
    return dispo;
}

void algo(workers_t *workers, projects_t *projects, int nw, int np)
{
    int day = 1;

    while (day < max_best_before) {
        for (size_t i = 0; i < np; i++) {
            if (projects[i].started) {
                projects[i].days -= 1;
                if (projects[i].days == 0) {
                    for (size_t o = 0; projects[i].workers && projects[i].workers[o]; o++) {
                        projects[i].workers[o]->in_use = 0;
                        for (size_t x = 0; x < projects[i].number_of_roles; x++) {
                            for (size_t c = 0; c < projects[i].workers[o]->number_of_comp; c++) {
                                if (projects[i].roles[x].name == projects[i].workers[o]->comps[c].name) {
                                    if (projects[i].workers[o]->comps[c].level <= projects[i].roles[x].level)
                                        projects[i].workers[o]->comps[c].level += 1;
                                }
                            }
                        }
                    }
                }
            }
        }

        projects_t **dispo_projects = get_dispo_projects(workers, projects, nw, np, day);

        for (size_t i = 0; dispo_projects && dispo_projects[i]; i++) {
            workers_t **dispo_w = get_dispo_worker(workers, dispo_projects[i]->roles, nw, dispo_projects[i]->number_of_roles);
            printf("%s\n", projects_name[dispo_projects[i]->name]);
            for (size_t o = 0; dispo_w && dispo_w[o]; o++) {
                if (dispo_w[o + 1])
                    printf("%s ", workers_name[dispo_w[o]->name]);
                else
                    printf("%s\n", workers_name[dispo_w[o]->name]);
                dispo_w[o]->in_use = 1;
            }
            for (size_t o = 0; o < nw; o++) {
                workers[o].score = 0;
                workers[o].dispo = 1;
            }
            dispo_projects[i]->started = 1;
            dispo_projects[i]->workers = dispo_w;
            dispo_projects = get_dispo_projects(workers, projects, nw, np, day);
            i = 0;
        }
        day++;
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

    algo(workers, projects, number_of_contributors, number_of_projects);
}