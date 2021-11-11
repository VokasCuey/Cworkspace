### P1817. 文件倒序
---
Description:

    从inp文件中读入数据，并倒序写入oup文件中，数据长度不超过1000


Input:

    没有输入数据。你需要从名为"inp"的文件中读入数据。


Output:

    你需要将所有的输出，写入名为"oup"的文件中。


Input Example:

    无

Output Example:

    无

Note：

    无
---
### P2412. 字符串查找（文件）
Description:

    输入两个字符串a，b，请输出a中第一次出现b的位置（a的字母位置从0开始编号）。

    例如，a=“1212121”, b=“212”，则应该输出1。

    若a中不存在b，则输出-1。


Input:

    从input.txt输入

    数据有2行。第一行为字符串a，第二行为字符串b。

    （所有字符串长度均不超过1000）


Output:

    输出到output.txt。

    输出a中b所在的位置下标（从0开始）。若不存在，则输出-1。


Input Example:

    The $x$ is very important.
    $x$

Output Example:

    4
Note:

    注意：input.txt只读，不可写。请不要尝试以写权限打开，否则会打开失败。
---
### P2413. 字符串替换（文件）
---
Description;

    输入三个字符串a，b，c，请把a种第一次出现的b替换为c。

    若a="1212121", b="212", c="@", 则替换后的字符串为"1@121"。


Input:

    从input.txt输入

    数据有3行。第一行为字符串a，第二行为字符串b，第三行为字符串c。

    （三个字符串长度均不超过1000）


Output:

    输出到output.txt文件中。

    输出替换后的字符串。若a中不包含b，则输出a。


Input Example:

    The $x$ is very important.
    $x$
    apple pen

Output Example:

    The apple pen is very important.

Note:

    无
---