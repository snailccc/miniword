void MainWindow::pasteaction()
{
    int i;
      background->text->t->copyline=background->text->t->getmarkcopy(background->text->t->markcopy);
      background->text->t->filechunkpaste(background->text->t->file,line,row,background->text->t->copyline);//第row个字符之后粘贴
      background->text->t->filestringprint(background->text->t->file);

      background->text->t->undo[background->text->t->posforundo].type=5;
   background->text->t->undo[background->text->t->posforundo].oldhang1=background->text->t->undo[background->text->t->posforundo].newhang1=line;
   background->text->t->undo[background->text->t->posforundo].oldlie1=row;
   background->text->t->undo[background->text->t->posforundo].newlie1=row+1;
   background->text->t->undo[background->text->t->posforundo].kuai=background->text->t->getmarkcopy(background->text->t->markcopy);
   if(markcopyx1==markcopyx2){//只粘贴一行
       background->text->t->undo[background->text->t->posforundo].newhang2=line;
       background->text->t->undo[background->text->t->posforundo].newlie2=row+markcopyy2-markcopyy1+1;
   }
   else if(markcopyx1+1<=markcopyx2)//及两行以上
   {
     background->text->t->undo[background->text->t->posforundo].newhang2=line+markcopyx2-markcopyx1;
     background->text->t->undo[background->text->t->posforundo].newlie2=markcopyy2;
   }
     background->text->t->posforundo++;
}
