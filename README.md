## MiniShell_42


## Разрешенные функции в проекте
| Функции для minishell | Инструкция | Link |
| --- | --- | --- |
| readline (const char *prompt); | Получает данные из командной строки, сохраняет историю, можно обращаться к историческим командам, для введенных char выделяет память через malloc (т.е. надо будет эту память потом освободить) _ENG: readline will read a line from the terminal and return it, using prompt as a prompt. If prompt is NULL or the empty string, no prompt is issued. The line returned is allocated with malloc(3); the caller must free it when finished. The line returned has the final newline removed, so only the text of the line remains. readline offers editing capabilities while the user is entering the line. By default, the line editing commands are similar to those of emacs. A vi-style line editing interface is also available_ | https://www.opennet.ru/man.shtml?topic=readline&category=3&russian=2 |
| void rl_clear_history (void) | RUS: Очищает историю введенных данных в командную строку, по аналогии с clear_history _ENG: Clear the history list by deleting all of the entries, in the same manner as the History library's clear_history() function. This differs from clear_history because it frees private data Readline saves in the history list._ | https://tiswww.case.edu/php/chet/readline/readline.html |
| int rl_on_new_line (void) | RUS: Сообщает функциям, что мы переместились на новую строку - Обычно после того, как была выведена новая строка _ENG: Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline._ | https://tiswww.case.edu/php/chet/readline/readline.html |
| void rl_replace_line (const char *text, int clear_undo) | RUS: Заменяет содержание rl_line_buffer текстом. Точка и отметка сохраняются, если это возможно. Если значение clear_undo не равно нулю, the undo list, связанный с текущей строкой, очищается.  _ENG: Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared_ | https://tiswww.case.edu/php/chet/readline/readline.html |
| void rl_redisplay (void) | RUS: Меняет текст, что отражается на экране, чтобы показать с текущее содержание rl_line_buffer  _ENG: Change what's displayed on the screen to reflect the current contents of rl_line_buffer._ | https://tiswww.case.edu/php/chet/readline/readline.html |
| void add_history (char *string) | RUS: Поместить string в конец перечня истории. В связанном поле данных (если оно есть) - устанавливается NULL _ENG: Place **string** at the end of the history list. The associated data field (if any) is set to NULL._ | http://www.math.utah.edu/docs/info/hist_2.html |
| #include<io.h> int access(const char * filename, int amode); | access проверяет файл c именем filename для определения, существует  ли  он,  может  ли он быть прочитан, записан или выполнен. _Список значений параметра amode:  06   проверка разрешения на чтение и запись;                    04   проверка разрешения на чтение;                    02   проверка разрешения на запись;                   01   проверка на выполнение (игнорируется);                    00   проверка на существование файла;            Примечание. Под  управлением  операционной  системы DOS  все  существующие файлы имеют доступ на чтение (amode равен 04),  поэтому 00 и 04 дают один и  тот же результат.  По той же причине значения параметра amode эквивалентны,  поскольку под DOS  доступ  для записи включает и доступ по чтению. Если параметр    filename   является   ссылкой   на директорию,  функция   access   просто   проверяет, существует данная директория или нет._ | http://www.codenet.ru/progr/cpp/spr/005.php |
| #include <sys/types.h> #include <unistd.h> pid_t fork(void);   | fork создает процесс-потомок, который отличается от родительского только значениями PID (идентификатор процесса) и PPID (идентификатор родительского процесса), а также тем фактом, что счетчики использования ресурсов установлены в 0. Блокировки файлов и сигналы, ожидающие обработки, не наследуются. Под Linux fork реализован с помощью "копирования страниц при записи" (copy-on-write, COW), поэтому расходы на fork сводятся к копирования таблицы страниц родителя и созданию уникальной структуры, описывающей задачу | https://www.opennet.ru/man.shtml?topic=fork&category=2 |
| #include <sys/types.h> #include <sys/wait.h> **pid_t wait(int *status)**; **pid_t waitpid(pid_t pid, int *status, int options)**;   | Функция wait приостанавливает выполнение текущего процесса до тех пор, пока дочерний процесс не завершится, или до появления сигнала, который либо завершает текущий процесс, либо требует вызвать функцию-обработчик. Если дочерний процесс к моменту вызова функции уже завершился (так называемый "зомби" ("zombie")), то функция немедленно возвращается. Системные ресурсы, связанные с дочерним процессом, освобождаются. Функция waitpid приостанавливает выполнение текущего процесса до тех пор, пока дочерний процесс, указанный в параметре pid, не завершит выполнение, или пока не появится сигнал, который либо завершает текущий процесс либо требует вызвать функцию-обработчик. Если указанный дочерний процесс к моменту вызова функции уже завершился (так называемый "зомби"), то функция немедленно возвращается. Системные ресурсы, связанные с дочерним процессом, освобождаются. Параметр pid может принимать несколько значений | https://www.opennet.ru/man.shtml?topic=wait&category=2&russian=0 |
| #include <sys/types.h> #include <sys/time.h> #include <sys/resource.h> #include <sys/wait.h> pid_t **wait3(int *status, int options,struct rusage *rusage)**; **pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage)**; | Функция wait3 приостанавливает исполнение текущего процесса до того, как дочерний процесс завершит свою работу, или он не получит сигнал, прекращающий его работу, или не будет произведен вызов обработчика прерывания. Если дочерний процесс уже прекратил свою работу на момент вызова этой функции (такой процесс называется "зомби" ("zombie")), то функция немедленно возвращается. Все системные ресурсы, использованные дочерним процессом, будут освобождены. Функция wait4 приостанавливает исполнение текущего процесса до того, как свою работу завершит дочерний процесс с номером pid, или этот процесс не получит сигнал, прекращающий его работу, или не будет произведен вызов обработчика прерывания. Если дочерний процесс pid уже прекратил свою работу на момент вызова этой функции (такой процесс называется "зомби"), то функция немедленно возвращается. Все системные ресурсы, использованные дочерним процессом, будут освобождены. | https://www.opennet.ru/man.shtml?topic=wait3&category=2&russian=0 |
| #include <signal.h> typedef void (*sighandler_t)(int); sighandler_t signal(int signum, sighandler_t handler); | Системный вызов signal() устанавливает новый обработчик сигнала с номером signum в соответствии с параметром sighandler, который может быть функцией пользователя, SIG_IGN или SIG_DFL. При получении процессом сигнала с номером signum происходит следующее: если устанавливаемое значение обработчика равно SIG_IGN, то сигнал игнорируется; если оно равно SIG_DFL, то выполняются стандартные действия, связанные с сигналом (см. signal(7)). Наконец, если обработчик установлен в функцию sighandler, то сначала устанавливает значение обработчика в SIG_DFL или выполняется зависимая от реализации блокировка сигнала, а затем вызывается функция sighandler с параметром signum. | https://www.opennet.ru/man.shtml?topic=signal&category=2&russian=0 |
| #include <signal.h> **int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact)**; **int sigprocmask(int how, const sigset_t *set, sigset_t *oldset)**; **int sigpending(sigset_t *set)**; **int sigsuspend(const sigset_t *mask)**;  | Системный вызов sigaction используется для изменения действий процесса при получении соответствующего сигнала. Параметр signum задает номер сигнала и может быть равен любому номеру, кроме SIGKILL и SIGSTOP. Если параметр act не равен нулю, то новое действие, связянное с сигналом signum, устанавливается соответственно act. Если oldact не равен нулю, то предыдущее действие записывается в oldact. | https://www.opennet.ru/man.shtml?topic=sigaction&category=2&russian=0 |
| #include <signal.h> **int sigemptyset(sigset_t *set)**; **int sigfillset(sigset_t *set)**; **int sigaddset(sigset_t *set, int signum)**; **int sigdelset(sigset_t *set, int signum)**; **int sigismember(const sigset_t *set, int signum)**; | Функции sigsetops(3) позволяют производить операции над наборами сигналов POSIX. _sigemptyset_ инициализирует набор сигналов, указанный в set, и "очищает" его от всех сигналов. _sigfillset_ полностью инициализирует набор set, в котором содержатся все сигналы. _sigaddset_ и _sigdelset_ добавляют сигналы signum к set и удаляют эти сигналы из набора соответственно. _sigismember_ проверяет, является ли signum членом set. | https://www.opennet.ru/man.shtml?topic=sigemptyset&category=3&russian=0 | 
| #include <sys/types.h> #include <signal.h> **int kill(pid_t pid, int sig)**; | Системный вызов kill может быть использован для посылки какого-либо сигнала какому-либо процессу или группе процесса. Если значение pid является положительным, сигнал sig посылается процессу с идентификатором pid. Если pid равен 0, то sig посылается каждому процессу, который входит в группу текущего процесса. Если pid равен -1, то sig посылается каждому процессу, за исключением процесса с номером 1 (init), но есть нюансы, которые описываются ниже. Если pid меньше чем -1, то sig посылается каждому процессу, который входит в группу процесса -pid. Если sig равен 0, то никакой сигнал не посылается, а только выполняется проверка на ошибку. | https://www.opennet.ru/man.shtml?topic=kill&category=2&russian=0 |
| #include <unistd.h> #include <stdlib.h> **void _Exit(int status)**; | _exit "немедленно" завершает работу программы. Все дескрипторы файлов, принадлежащие процессу, закрываются; все его дочерние процессы начинают управляться процессом 1 (init), а родительскому процессу посылается сигнал SIGCHLD. Значение status возвращается родительскому процессу как статус завершаемого процесса; он может быть получен с помощью одной из функций семейства wait. Функция _Exit эквивалентна функции _exit.  | https://www.opennet.ru/man.shtml?topic=exit&category=2&russian=0 |
| #include <unistd.h> **char *getcwd(char *buf, size_t size)**; **char *get_current_dir_name(void)**; **char *getwd(char *buf)**; | Функция **getcwd**() копирует абсолютный путь к текущему рабочему каталогу в массиве, на который указывает buf, имеющий длину size. Если текущий абсолютный путь требует буфера, длина которого превышает size, то возвращается NULL, а errno принимает значение ERANGE; приложение должно проверить, возникла эта ошибка или нет и, если необходимо, выделить буфер большего размера. Если buf равно NULL, то поведение getcwd() становится неопределенным. Расширение стандарта POSIX.1 для Linux (libc4, libc5, glibc) предусматривает следующее: если при вызове buf равно NULL, getcwd(), то буфер выделяется динамически с помощью функции malloc(). В этом случае выделенный буфер имеет размер size; если size равно нулю, то выделяется buf необходимого размера. Возможно (и даже рекомендуется) после использования освободить выделенные таким образом буферы с помощью free().  get_current_dir_name (которая имеет прототип только в том случае, если определено значение _GNU_SOURCE) выделит с помощью malloc(3) массив, достаточно большой для помещения в него имени текущего каталога. Если установлена и имеет правильное значение переменная окружения PWD, то будет возвращено ее значение. getwd (имеющая прототип только в том случае, если определено значение _BSD_SOURCE или _XOPEN_SOURCE_EXTENDED) не будет выделять память с помощью malloc(3). Аргумент buf должен быть указателем на массив длиной как минимум PATH_MAX байтов. getwd возвращает только первые PATH_MAX байтов реального пути. | https://www.opennet.ru/man.shtml?topic=getcwd&category=3&russian=0 |
| #include <unistd.h> **int chdir(const char *path)**; **int fchdir(int fd)**; | **chdir** изменяет текущий каталог каталог на path. fchdir идентично chdir, только каталог задан в виде открытого файлового дескриптора. | https://www.opennet.ru/cgi-bin/opennet/man.cgi?topic=chdir&category=2 |
| #include <sys/types.h> #include <sys/stat.h> #include <unistd.h> **int stat(const char *file_name, struct stat *buf)**; **int fstat(int filedes, struct stat *buf)**; **int lstat(const char *file_name, struct stat *buf)**; | Эти функции возвращают информацию об указанном файле. Для этого не требуется иметь права доступа к файлу, хотя потребуются права поиска во всех каталогах, указанных в полном имени файла. stat возвращает информацию о файле file_name и заполняет буфер buf. lstat идентична stat, но в случае символьных сылок она возвращает информацию о самой ссылке, а не о файле, на который она указывает. fstat идентична stat, только возвращается информация об открытом файле, на который указывает filedes (возвращаемый open(2)), а не о file_name. Детали по структуре stat https://github.com/bakyt92/09_minishell/blob/master/README.md#%D1%81%D1%82%D1%80%D1%83%D0%BA%D1%82%D1%83%D1%80%D0%B0-%D0%B4%D0%BB%D1%8F-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8-stat | https://www.opennet.ru/man.shtml?topic=stat&category=2&russian=0 |
| #include <unistd.h> **int unlink(const char *pathname)**; | **unlink** удаляет имя из файловой системы. Если это имя было последней ссылкой на файл и больше нет процессов, которые держат этот файл открытым, данный файл удаляется и место, которое он занимает освобождается для дальнейшего использования. Если имя было посленей ссылкой на файл, но какие-либо процессы всё ещё держат этот файл открым, файл будет оставлен пока последний файловый дескриптор, указывающий на него, не будет закрыт. Если имя указывает на символьную ссылку, ссылка будет удалена. Если имя указывает на сокет, FIFO или устройство, имя будет удалено, но процессы, которые открыли любой из этих объектов могут продолжать его использовать.   | https://www.opennet.ru/man.shtml?topic=unlink&category=2&russian=0 |
| #include <unistd.h> **int execve(const char *filename, char *const argv [], char *const envp[])**; | execve() выполняет программу, заданную параметром filename. Программа должна быть или двоичным исполняемым файлом, или скриптом, начинающимся со строки вида "#! интерпретатор [аргументы]". В последнем случае интерпретатор -- это правильный путь к исполняемому файлу, который не является скриптом; этот файл будет выполнен как интерпретатор [arg] filename. argv -- это массив строк, аргументов новой программы. envp -- это массив строк в формате key=value, которые передаются новой программе в качестве окружения (environment). Как argv, так и envp завершаются нулевым указателем. К массиву аргументов и к окружению можно обратиться из функции main(), которая объявлена как int main(int argc, char *argv[], char *envp[]). execve() не возвращает управление при успешном выполнении, а код, данные, bss и стек вызвавшего процесса перезаписываются кодом, данными и стеком загруженной программы. Новая программа также наследует от вызвавшего процесса его идентификатор и открытые файловые дескрипторы, на которых не было флага закрыть-при-exec (close-on-exec, COE). Сигналы, ожидающие обработки, удаляются. Переопределённые обработчики сигналов возвращаются в значение по умолчанию. Обработчик сигнала SIGCHLD (когда установлен в SIG_IGN) может быть сброшен или не сброшен в SIG_DFL. Если текущая программа выполнялась под управлением ptrace, то после успешного execve() ей посылается сигнал SIGTRAP. Если на файле программы filename установлен setuid-бит, то фактический идентификатор пользователя вызывавшего процесса меняется на идентификатор владельца файла программы. Точно так же, если на файле программы установлен setgid-бит, то фактический идентификатор группы устанавливается в группу файла программы. Если исполняемый файл является динамически-скомпонованным файлом в формате a.out, содержащим заглушки для вызова разделяемых библиотек, то в начале выполнения этого файла вызывается динамический компоновщик ld.so(8), который загружает библиотеки и компонует их с исполняемым файлом. Если исполняемый файл является динамически-скомпонованным файлом в формате ELF, то для загрузки разделяемых библиотек используется интерпретатор, указанные в сегменте PT_INTERP. Обычно это /lib/ld-linux.so.1 для программ, скомпилированных под Linux libc версии 5, или же /lib/ld-linux.so.2 для программ, скомпилированных под GNU libc версии 2. | https://www.opennet.ru/man.shtml?topic=execve&category=2&russian=0 |
| #include <unistd.h> **int dup(int oldfd)**; **int dup2(int oldfd, int newfd)**; | dup и dup2 создают копию файлового дескриптора oldfd. Старый и новый дескрипторы можно использовать друг вместо друга. Они имеют общие блокировки, указатель позиции в файле и флаги; например, если позиция в файле была изменена с помощью lseek, на одном из дескрипторов, то эта позиция также меняется и на втором. Два дескриптора, однако, каждый имеют свой собственный флаг закрыть-при-exec. dup использует самый маленький свободный номер дескриптора. dup2 делает newfd копией oldfd, закрывая newfd, если требуется.   | https://www.opennet.ru/man.shtml?topic=dup&category=2&russian=0 |
| #include <unistd.h> **int pipe(int filedes[2])**;   | pipe создает пару файловых описателей, указывающих на запись inode именованного канала, и помещает их в массив, на который указывает filedes. filedes[0] предназначен для чтения, а filedes[1] предназначен для записи.  | https://www.opennet.ru/man.shtml?topic=pipe&category=2&russian=0 |
| #include <sys/types.h> #include <dirent.h> **DIR *opendir(const char *name)**; | Функция opendir() открывает поток каталога, соответствующий каталогу name, и возвращает указатель на этот поток. Поток устанавливается на первой записи в каталоге. | https://www.opennet.ru/man.shtml?topic=opendir&category=3&russian=0 |
| #include <sys/types.h> #include <dirent.h> **struct dirent *readdir(DIR *dir)**; | Функция readdir() возвращает указатель на следующую запись каталога в структуре dirent, прочитанную из потока каталога. Каталог указан в dir. Функция возвращает NULL по достижении последней записи или если была обнаружена ошибка. В соответствие с POSIX, структура dirent содержит поле char d_name[] неопределенной длины, с максимальным количеством символов, предшествующих конечному нулевому символу, равным NAME_MAX. Использование других полей отрицательно повлияет на переносимость ваших программ. В POSIX-2001 как расширение XSI описано поле ino_t d_ino. Данные, возвращаемые readdir() могут быть переписаны последующими вызовами readdir() для того же каталожного потока. | https://www.opennet.ru/cgi-bin/opennet/man.cgi?topic=readdir&category=3 |
| #include <sys/types.h> #include <dirent.h> int closedir(DIR *dir); | Функция closedir() закрывает поток, связанный с каталогом dir. Описатель потока dir будет недоступен после вызова этой функции | https://www.opennet.ru/man.shtml?topic=closedir&category=3&russian=0 |
| #include <string.h> char *strerror(int errnum); int strerror_r(int errnum, char *buf, size_t n); | Функция strerror() возвращает строку, описывающую код ошибки, переданный в аргументе errnum, возможно с учетом категории LC_MESSAGES текущей локали для выбора соответсвующего языка. Приложение не должно изменять строку. Строка может измениться при последующем вызовом perror() или strerror(). В библиотеке нет функций изменяющих эту строку. Функция strerror_r() аналогична strerror(), но безопасна с точки зрения подпроцессов (threads). Она возвращает строку в буфере buf, предоставленном пользователем и имеющим длину n. | https://www.opennet.ru/man.shtml?topic=strerror&category=3&russian=0 |
| #include <stdio.h> **void perror(const char *s)**; #include <errno.h> const char *sys_errlist[]; int sys_nerr;   | Процедура perror() выводит в стандартный поток ошибки сообщения, описывая ошибку, произошедшую при последнем системном вызове или вызове библиотечной функции. Сначала (если s не равно NULL и *s не равно NULL) выводится строка s, затем двоеточие, пробел и сообщение, завершающееся переводом строки. Для большего удобства параметы строки должны содержать имя функции, вызвавшей ошибку. Номер ошибки извлекается из внешней переменной errno, которая устанавливается в случае ошибки, но не "очищается" в случае нормального завершения работы. Глобальный список ошибок sys_errlist[], упорядоченный в соответствии с errno, может быть использован для вывода сообщений об ошибке без перевода строки. Наибольший номер в таблице имеет sys_nerr -1. Будьте осторожны при непосредственном использовании этого массива. Новые элементы не могут быть вписаны в sys_errlist[]. Если системный вызов завершается ошибкой, то возвращается -1 и переменная errno устанавливается равной коду ошибки (эти величины могут быть найдены в <errno.h>). Многие системные функции работают именно так. Функция perror() позволяет отображать коды ошибок в понятном человеку виде. Заметьте, что errno не является определенной после нормального завершения системного вызова: этот вызов может изменить переменную кода ошибки, даже если завершился удачно (например, потому, что он использовал другие функции, завершившиеся ошибкой). Таким образом, если за вызовом, завершившимся ошибкой, непосредственно не следует perror, то величина errno должна быть сохранена | https://www.opennet.ru/man.shtml?topic=perror&category=3&russian=0 |
| #include <unistd.h> **int isatty(int desc)**; | isatty - определяет, ссылается ли данный описатель на терминал. Возвращает 1, если desc является открытым описателем, соединенным с терминалом, в противном случае возвращает 0. | https://www.opennet.ru/man.shtml?topic=isatty&category=3&russian=0 |
| #include <unistd.h> **char *ttyname(int fd)**; **int ttyname_r(int fd, char *buf, size_t buflen)**; | Функция ttyname() возвращает указатель на полное имя устройства терминала, заканчивающееся на NUL, открытого на описателе файла fd, или NULL при ошибках (например, если fd не подключен к терминалу). Возвращаемое значение может указывать на статические данные, которые могут быть перезаписаны следующим вызовом. Функция ttyname_r() сохраняет полный путь в буфере buf длиной buflen. | https://www.opennet.ru/man.shtml?topic=ttyname&category=3&russian=0 |
| #include <unistd.h> /* для систем BSD */ #include <stdlib.h> /* для систем SYSV */ **int ttyslot(void);**   | ttyslot - поиск слота текущего терминала пользователя в некотором файле  Функция ttyslot() возвращает индекс текущей записи пользователя в некотором файле. | https://www.opennet.ru/man.shtml?topic=ttyslot&category=3&russian=0 |
| #include <sys/ioctl.h> int ioctl(int d, int request, ...); | Функция ioctl манипулирует базовыми параметрами устройств, представленных в виде специальных файлов. В частности, многими оперативными характеристиками специальных символьных файлов (например терминалов) можно управлять через ioctl запросы. В качестве аргумента d должен быть указан открытый файловый дескриптор. Второй аргумент является кодом запроса, который зависит от устройства. Третий аргумент является указателем на память, который не имеет типа. Традиционно это char *argp (до тех пор пока в C не появился void * ). Ioctl запрос request кодирует в себе либо аргумент, который является параметром in либо аргумент, который является параметром out и кроме того размер аргумента argp в байтах. Макросы и определения, используемые в специальных ioctl запросах request находятся в файле <sys/ioctl.h>. | https://www.opennet.ru/man.shtml?topic=ioctl&category=2&russian=0 |
| #include <stdlib.h> **char *getenv(const char *name);** | Функция getenv() ищет в списке окружения строку, совпадающую со строкой, указанной в name. Строки имеют вид имя = значение | https://www.opennet.ru/man.shtml?topic=getenv&category=3&russian=0 |
| #include <unistd.h> **pid_t tcgetpgrp(int fd)**; **int tcsetpgrp(int fd, pid_t pgrp)**;   | tcgetpgrp, tcsetpgrp - получение и определение основной группы процессов терминала. Функция tcgetpgrp() возвращает идентификатор группы процессов для основной группы процессов терминала, ассоциированного с fd, который должен быть управляющим терминалом для вызывающего процесса.Функция tcsetpgrp() делает группу процессов с идентификатором pgrp основной группой процессов на терминале, ассоциированном с fd, который должен быть управляющим терминалом для вызывающего процесса, и все еще быть ассоциированным с его сессией. Более того, pgrp должно быть (непустой) группой процессов, принадлежащих к той же сессии, что и вызывающий процесс. Если tcsetpgrp() вызывается членом группы фоновых процессов в этой сессии, и вызывающий процесс не блокирует или игнорирует SIGTTOU, то сигнал SIGTTOU отправляется всем членам этой группы фоновых процессов. | https://www.opennet.ru/man.shtml?topic=tcsetattr&category=3&russian=0 |
| #include <termios.h> **int tcsetattr(int fildes, int optional_actions, const struct termios *termios_p)**; | tcsetattr - set the parameters associated with the terminal. The tcsetattr() function shall set the parameters associated with the terminal referred to by the open file descriptor fildes (an open file descriptor associated with a terminal) from the termios structure referenced by termios_p as follows: If optional_actions is TCSANOW, the change shall occur immediately. If optional_actions is TCSADRAIN, the change shall occur after all output written to fildes is transmitted. This function should be used when changing parameters that affect output. If optional_actions is TCSAFLUSH, the change shall occur after all output written to fildes is transmitted, and all input so far received but not read shall be discarded before the change is made. | https://pubs.opengroup.org/onlinepubs/009696799/functions/tcsetattr.html |
| #include <termios.h> **int tcgetattr(int fildes, struct termios *termios_p)**; | The **tcgetattr()** function shall get the parameters associated with the terminal referred to by fildes and store them in the termios structure referenced by _termios_p_. The fildes argument is an open file descriptor associated with a terminal. The _termios_p_ argument is a pointer to a termios structure. The _tcgetattr()_ operation is allowed from any process. If the terminal device supports different input and output baud rates, the baud rates stored in the termios structure returned by tcgetattr() shall reflect the actual baud rates, even if they are equal. If differing baud rates are not supported, the rate returned as the output baud rate shall be the actual baud rate. If the terminal device does not support split baud rates, the input baud rate stored in the termios structure shall be the output rate (as one of the symbolic values). | https://pubs.opengroup.org/onlinepubs/007904975/functions/tcgetattr.html |
| #include <term.h> **int tgetent(char *bp, const char *name)**; | The tgetent() function looks up the termcap entry for name. The emulation ignores the buffer pointer bp. | https://pubs.opengroup.org/onlinepubs/7908799/xcurses/tgetent.html |
| int tgetflag(char id[2]); | The tgetflag() function gets the boolean entry for id. | https://pubs.opengroup.org/onlinepubs/7908799/xcurses/tgetent.html |
| int tgetnum(char id[2]); | The tgetnum() function gets the numeric entry for id. | https://pubs.opengroup.org/onlinepubs/7908799/xcurses/tgetent.html |
| char *tgetstr(char id[2], char **area); | The tgetstr() function gets the string entry for id. If area is not a null pointer and does not point to a null pointer, tgetstr() copies the string entry into the buffer pointed to by *area and advances the variable pointed to by area to the first byte after the copy of the string entry. | https://pubs.opengroup.org/onlinepubs/7908799/xcurses/tgetent.html |
| char *tgoto(char *cap, int col, int row); | The tgoto() function instantiates the parameters col and row into the capability cap and returns a pointer to the resulting string | https://pubs.opengroup.org/onlinepubs/7908799/xcurses/tgetent.html |
|  |  |  |

##### Отличия wait3 / wait4 от waitpid и wait
В wait3/4 есть аргумент rusage, который в формате структуры возникает из команды getrusage (как я понял)

getrusage возвращает текущие ограничения на ресурсы для who, который может быть или RUSAGE_SELF или RUSAGE_CHILDREN. Первое запрашивает информацию о ресурсах используемых текущим процессом, а второе о тех порожденных процессах, которые завершились или завершение которых ожидается.

struct rusage {
        struct timeval ru_utime;        /* время работы пользователя */
        struct timeval ru_stime;        /* использованное системное время */
        long    ru_maxrss;              /* максимальный rss */
        long    ru_ixrss;               /* общий объем разделяемой памяти */
        long    ru_idrss;               /* общий объем неразделяемых данных */
        long    ru_isrss;               /* общий объем неразделяемых стеков */
        long    ru_minflt;              /* количество процессов подгрузки страницы */
        long    ru_majflt;              /* количество ошибок при обращении к странице */
        long    ru_nswap;               /* количество обращений к диску при подкачке */
        long    ru_inblock;             /* количество операций блокового ввода */
        long    ru_oublock;             /* количество операций блокового вывода */
        long    ru_msgsnd;              /* количество отправленных сообщений */
        long    ru_msgrcv;              /* количество принятых сообщений */
        long    ru_nsignals;            /* количество принятых сигналов */
        long    ru_nvcsw;               /* количество переключений контекста процессом */
        long    ru_nivcsw;              /* количество принудительных переключений контекста */
};

##### Структура для функции stat

Все эти функции возвращают структуру stat, которая содержит следующие поля:

struct stat {
    dev_t         st_dev;      /* устройство */
    ino_t         st_ino;      /* inode */
    mode_t        st_mode;     /* режим доступа */
    nlink_t       st_nlink;    /* количество жестких ссылок */
    uid_t         st_uid;      /* идентификатор пользователя-владельца */
    gid_t         st_gid;      /* идентификатор группы-владельца */
    dev_t         st_rdev;     /* тип устройства */
                               /* (если это устройство) */
    off_t         st_size;     /* общий размер в байтах */
    blksize_t     st_blksize;  /* размер блока ввода-вывода */
                               /* в файловой системе */
    blkcnt_t      st_blocks;   /* количество выделенных блоков */
    time_t        st_atime;    /* время последнего доступа */
    time_t        st_mtime;    /* время последней модификации */
    time_t        st_ctime;    /* время последнего изменения */
};

***
#### Большое спасибо @bakyt92 за собранную информацию!
***

@SSenpo
