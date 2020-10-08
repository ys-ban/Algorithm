#-*- encoding: utf-8 -*-
import os

url_head = "https://github.com/ys-ban/algorithm/blob/main/BOJ/"

base_text = """# django-tutorial
<ul>
<li>파이썬 웹 프레임워크 django 공부를 위한 repo</li>
<li>우선은 Class Based View 위주로 공부</li>
<li>교재는 파이썬 웹 프로그래밍 실전편</li>
</ul>
<br>
<br>
<ul>
"""

def make_list():
    dir_list = os.listdir("BOJ/")
    ret = []
    q_list = []
    nq_list = []
    for elem in dir_list :
        file_name = elem.split(".")[0]
        if (file_name[0]=='q') :
            file_name = file_name[1:]
            name_split = file_name.split("_")
            q_list.append((int(name_split[0]), "q"+file_name))
        else :
            nq_list.append(file_name)
    ret.append(nq_list)
    q_list.sort()
    ret.append(q_list)
    return ret

def make_readme():
    f = open("README.md", "w", encoding='utf-8')
    f.write(base_text)
    prob_list = make_list()
    pre_num = 0
    sub_num = 1
    for elem in prob_list[0] :
        f.write('<li><a href="'+url_head+elem+'.cpp">'+elem+'</li>\n')
    for num, file_name in prob_list[1] :
        if pre_num==num :
            f.write('<li><a href="'+url_head+file_name+'.cpp">'+str(num)+'('+sub_num+')'+'</li>\n')
            sub_num = sub_num+1
        else :
            f.write('<li><a href="'+url_head+file_name+'.cpp">'+str(num)+'</li>\n')
            pre_num = num
            sub_num = 1
    f.write('</ul>')
    f.close()

make_readme()
