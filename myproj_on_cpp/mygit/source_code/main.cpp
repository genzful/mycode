#include <cstdlib>    // for getenv()
#include <filesystem> // for path of files or dirs
#include <fstream>    // for read || write files
#include <iostream>   // for cin
#include <print>      // thats std::println from c++23
#include <set>        // set in main func for fun)
#include <vector>     // for vector

using namespace std;
namespace fs = filesystem;

const string HOMEDIR = getenv("HOME");              // /home/arch
const string curpath = fs::current_path().string(); // current path working dir

int whichnumdir(bool now = false) {
  vector<string> files; // vector of dirs

  // cycle for filling vector by dirs at .mygit
  for (const auto &it : fs::directory_iterator(HOMEDIR + "/.mygit/")) {
    files.push_back(it.path().filename().string());
  }

  if (files.empty()) {
    return 1; // No directories yet
  }

  // taking last digit of last dir
  string last = files.back();
  int sym = 0;
  for (char c : last) {
    if (isdigit(c)) {
      sym = sym * 10 + (c - '0');
    }
  }

  if (now) {
    return sym;
  } else {
    return (sym + 1);
  }
}

string nameofdir(const string &dir) {
  fs::path path(dir);
  return path.filename().string();
}

string namedir(const string &file) {
  fs::path path(file);
  return path.stem().string(); // returns filename without extension
}

// function for take a next number for created file
int whichnum(const string &dir, const string &filename) {
  int max_num = 0;

  for (const auto &entry : fs::directory_iterator(dir)) {
    string fname = entry.path().stem().string();

    if (fname.find(filename) == 0) {
      string num_part = fname.substr(filename.length());
      int num = stoi(num_part);
      max_num = max(max_num, num);
    }
  }
  return ++max_num;
}

// function that show u, is dir was already exists at curpath or nouu brah
bool is_exists() {
  string dirsearch = HOMEDIR + "/.mygit/";
  string current_dir_name = nameofdir(curpath);

  if (!fs::exists(dirsearch)) {
    fs::create_directory(dirsearch);
    return false;
  }

  for (const auto &it : fs::directory_iterator(dirsearch)) {
    if (it.is_directory()) {
      string dir_name = it.path().filename().string();
      if (dir_name == current_dir_name) {
        return true;
      }
    }
  }

  return false;
}

void copyFileToRepo(const string &source, const string &destination) {
  ifstream src(source, ios::binary);
  ofstream dst(destination, ios::binary);

  if (!src.is_open() || !dst.is_open()) {
    throw runtime_error("Failed to open files for copying");
  }

  dst << src.rdbuf();

  src.clear();
  dst.clear();
  src.seekg(0, ios::end);
  dst.seekp(0, ios::end);

  if (src.tellg() != dst.tellp()) {
    throw runtime_error("Copy failed: size mismatch");
  }
}

// structure of storage
string createRepoStructure(const string &file_name, bool dir_exists) {
  string repo_dir = HOMEDIR + "/.mygit/" + nameofdir(curpath) + '/';

  if (!fs::exists(repo_dir)) {
    fs::create_directories(repo_dir);
  }

  string file_dir = repo_dir + file_name + '/';
  return file_dir;
}

// func for a writing a comment
void write_a_comment(const string &filepath, const string &comment) {
  vector<string> comments;
  if (fs::exists(filepath)) {
    ifstream readfile(filepath);
    string line;
    while (getline(readfile, line)) {
      if (line == comment) {
        throw runtime_error("this comment already exists at rep");
      }
      comments.push_back(line);
    }
    readfile.close();
  }

  ofstream writefile(filepath);
  if (!writefile) {
    throw runtime_error("Cannot open file for comment: " + filepath);
  }

  for (const auto &c : comments) {
    writefile << c << "\n";
  }

  writefile << comment << "\n";
}

// func which check the difference
bool check_difference(const string &path_in, const string &path_for_check) {
  if (!fs::exists(path_in) || !fs::exists(path_for_check)) {
    return true;
  }

  ifstream f1(path_in, ios::binary);
  ifstream f2(path_for_check, ios::binary);

  if (!f1.is_open() || !f2.is_open()) {
    return true;
  }

  string content1((istreambuf_iterator<char>(f1)), istreambuf_iterator<char>());
  string content2((istreambuf_iterator<char>(f2)), istreambuf_iterator<char>());

  return content1 != content2;
}

// function for create file or directory
void create(int &argc, char *argv[]) {
  if (argc != 4) {
    throw runtime_error("no comment");
  }
  string file_name = namedir(argv[2]);

  // check if repository for this file already exists
  bool dir_exists = is_exists();
  string file_dir = createRepoStructure(file_name, dir_exists);

  if (fs::exists(file_dir)) {
    println("Repository for file '{}' already exists!", file_name);
    return;
  }

  fs::create_directories(file_dir);

  // determine file number
  int file_num = 1;

  // create destination file path
  string filepath = file_dir + file_name + to_string(file_num) + ".txt";

  // copy the file
  try {
    copyFileToRepo(argv[2], filepath);

    // ЗАПИСЬ КОММЕНТАРИЯ ПРИ СОЗДАНИИ (добавлено)
    string path_to_comment = file_dir + "/comments.txt";
    write_a_comment(path_to_comment, argv[3]);

    if (fs::exists(HOMEDIR + "/.mygit/" + nameofdir(curpath) + '/')) {
      println("Created version {} for file '{}'", file_num, file_name);
    } else {
      println("Created initial repository for file '{}'", file_name);
    }
  } catch (const exception &e) {
    println("{}", e.what());
    return;
  }
}

// commit func
void commit(int &argc, char *argv[]) {
  if (argc == 4) {
    string fullpath =
        HOMEDIR + "/.mygit/" + nameofdir(curpath) + '/' + namedir(argv[2]);

    if (!fs::exists(fullpath)) {
      throw runtime_error("no created git dir");
    }

    string path_in = curpath + '/' + argv[2];
    string path_to = fullpath + '/' + namedir(argv[2]) +
                     to_string((whichnum(fullpath, namedir(argv[2])))) + ".txt";

    string path_for_check =
        fullpath + '/' + namedir(argv[2]) +
        to_string((whichnum(fullpath, namedir(argv[2])) - 1)) + ".txt";

    if (check_difference(path_in, path_for_check)) {
      string path_to_comment = HOMEDIR + "/.mygit/" + nameofdir(curpath) + '/' +
                               namedir(argv[2]) + "/comments.txt";
      write_a_comment(path_to_comment, argv[3]);
      copyFileToRepo(path_in, path_to);
      println("Committed new version with comment: {}", argv[3]);
    } else {
      println("no changes at commit");
    }
  } else {
    throw runtime_error("no comment");
  }
}

// func for delete rep at .mygit
void delete_rep(char *argv[]) {
  string path_to_delete =
      HOMEDIR + "/.mygit/" + nameofdir(curpath) + '/' + namedir(argv[2]);

  if (fs::exists(path_to_delete)) {
    try {
      fs::remove_all(path_to_delete);
      println("Successfully deleted main directory");
    } catch (const exception &e) {
      println("error {}", e.what());
    }
  } else {
    println("Main directory doesn't exist at: {}", path_to_delete);
  }
}

// back_to func (will be)
void back_to(int &argc, char *argv[]) {
  if (argc == 4) {
    string version_file = HOMEDIR + "/.mygit/" + nameofdir(curpath) + '/' +
                          namedir(argv[2]) + '/' + namedir(argv[2]) + argv[3] +
                          ".txt";

    println("Восстанавливаю из: {}", version_file);

    if (fs::exists(version_file)) {
      try {
        bool choise;
        string input;

        println("Комитить текущий файл перед восстановлением?\nда/1 - "
                "да\nнет/0 - нет");
        cin >> input;

        if (input == "да" || input == "1") {
          choise = true;
        } else if (input == "нет" || input == "0") {
          choise = false;
        } else {
          throw runtime_error("Некорректный выбор");
        }

        if (choise) {
          commit(argc, argv);
        }
        string current_file = curpath + '/' + argv[2];
        copyFileToRepo(version_file, current_file);
        println("✓ Файл '{}' успешно восстановлен до версии {}", argv[2],
                argv[3]);

      } catch (const exception &e) {
        println("Ошибка: {}", e.what());
      }
    } else {
      println("Версия {} не найдена для файла '{}'", argv[3], namedir(argv[2]));
    }
  } else {
    println("Использование: back_to <файл> <номер_версии>");
  }
}

// show func
void show_commits(char *argv[]) {
  string path_to_comment = HOMEDIR + "/.mygit/" + nameofdir(curpath) + '/' +
                           namedir(argv[2]) + "/comments.txt";
  if (!fs::exists(path_to_comment)) {
    throw runtime_error("no such comments file");
  }
  ifstream readfile(path_to_comment);
  string line;
  int count(1);
  while (getline(readfile, line)) {
    println("{}: {}", count, line);
  }
}

// func for showing repositories
void showrepo() {
  string mygit_dir = HOMEDIR + "/.mygit/";

  if (!fs::exists(mygit_dir)) {
    println("No repositories found.");
    return;
  }

  println("Available repositories:");

  int repo_count = 0;

  for (const auto &project_entry : fs::directory_iterator(mygit_dir)) {
    if (project_entry.is_directory()) {
      string project_name = project_entry.path().filename().string();
      println("\nProject: {}", project_name);
      println("   Files tracked:");

      int file_count = 0;
      for (const auto &file_entry :
           fs::directory_iterator(project_entry.path())) {
        if (file_entry.is_directory()) {
          string filename = file_entry.path().filename().string();

          int version_count = 0;
          for (const auto &version_entry :
               fs::directory_iterator(file_entry.path())) {
            if (version_entry.is_regular_file() &&
                version_entry.path().extension() == ".txt" &&
                version_entry.path().filename().string() != "comments.txt") {
              version_count++;
            }
          }

          println("   - {} ({} versions)", filename, version_count);
          file_count++;
        }
      }

      if (file_count == 0) {
        println("    No files tracked");
      }

      repo_count++;
    }
  }

  if (repo_count == 0) {
    println("No repositories found.");
  } else {
    println("\nTotal repositories: {}", repo_count);
  }
}

string help() {
  return "usage:\n\t<bin> <command> <file> <number of commit (if u call backto "
         "func)>\n\tmygit create main.cpp\n\tmygit showrepo\n\tmygit showcom "
         "main.cpp\n\tmygit backto main.cpp 2\n\n\tcreate need 1 "
         "argument\n\tcommit need 1 argument\n\tdelete need 1 "
         "argument\n\tbackto need 2 arguments (mygit backto <your file> "
         "<number of commit>)\n\tshowcom need 1 argument\n\tshowrepo dont need "
         "arguments at all\n\nGOOD LUCK!";
}

// main func
int main(int argc, char *argv[]) {
  if (argc > 1) {
    try {
      if (static_cast<string>(argv[1]) == "create") {
        create(argc, argv);
      } else if (static_cast<string>(argv[1]) == "commit") {
        commit(argc, argv);
      } else if (static_cast<string>(argv[1]) == "delete") {
        delete_rep(argv);
      } else if (static_cast<string>(argv[1]) == "backto") {
        back_to(argc, argv);
      } else if (static_cast<string>(argv[1]) == "showcom") {
        show_commits(argv);
      } else if (static_cast<string>(argv[1]) == "showrepo") {
        showrepo();
      } else if (static_cast<string>(argv[1]) == "--help") {
        println("{}", help());
      } else {
        println("wrong command!");
      }
    } catch (const exception &e) {
      println("Error: {}", e.what());
      return 1;
    }
  } else {
    if (argc == 3 && fs::exists(curpath + '/' + argv[2])) {
      println("File '{}' not found in current directory", argv[2]);
    } else {
      println("error of arguments");
      println("--help for help");
    }
  }
  return 0;
}
