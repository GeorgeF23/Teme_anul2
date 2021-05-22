#include <bits/stdc++.h>

using namespace std;

struct person {
    string name;
    set<string> emails;
};

bool compare_people(person a, person b) {
    if (a.emails.size() < b.emails.size()) return true;
    if (a.emails.size() == b.emails.size() && a.name.compare(b.name) < 0)
        return true;
    return false;
}

/**
 * @brief  Get only the unique people from a list of people
 * @note   
 * @param  people: list of people
 * @retval list of unique people
 */
vector<person> get_unique_people(vector<person> people) {
    int length = people.size();
    vector<person> unique_people;
    unordered_map<string, int> emails;

    vector<set<int>> groups;
    vector<int> group_id(length, -1);

    // Put every person in groups
    for (int i = 0; i < length; i++) {
        int other = -1;
        for (const string &email : people[i].emails) {
            if (emails.count(email) > 0) {
                other = emails[email];
                groups[group_id[other]].insert(i);
                group_id[i] = group_id[other];

            } else {
                emails.insert(make_pair(email, i));
            }
        }

        if (other == -1 && group_id[i] == -1) {
            group_id[i] = groups.size();
            groups.push_back({i});
        }
    }

    // Union all groups with common elements
    for (int i = 0; i < (int)groups.size(); i++) {
        for (auto &el : groups[i]) {
            if (group_id[el] != i) {
                groups[group_id[el]].insert(groups[i].begin(), groups[i].end());
                for (auto &el2 : groups[i]) {
                    group_id[el2] = group_id[el];
                }

                groups[i] = {};
                break;
            }
        }
    }

    // Merge all people from a group
    int index = 0;
    for (auto &group : groups) {
        if (group.size() == 0) continue;

        unique_people.push_back(people[*group.begin()]);

        for (auto &person_index : group) {
            for (const string &email : people[person_index].emails) {
                unique_people[index].emails.insert(email);
            }
        }
        index++;
    }

    return unique_people;
}

// A, B, C
// C -> A
// C -> B

int main() {
    ifstream in;
    ofstream out;

    in.open("adrese.in");
    out.open("adrese.out");

    // Read input
    int n;
    in >> n;

    // Read input
    vector<person> people(n);
    for (int i = 0; i < n; i++) {
        int no_emails;
        in >> people[i].name;
        in >> no_emails;

        for (int j = 0; j < no_emails; j++) {
            string email;
            in >> email;

            people[i].emails.insert(email);
        }
    }

    // Compute unique people
    vector<person> unique_people = get_unique_people(people);

    // Sort by name
    sort(unique_people.begin(), unique_people.end(), compare_people);
    // Print result
    int no_unique_people = unique_people.size();
    out << no_unique_people << "\n";

    for (int i = 0; i < no_unique_people; i++) {
        out << unique_people[i].name << " ";
        out << unique_people[i].emails.size() << "\n";
        for (const string &email : unique_people[i].emails) {
            out << email << "\n";
        }
    }

    in.close();
    out.close();
    return 0;
}
