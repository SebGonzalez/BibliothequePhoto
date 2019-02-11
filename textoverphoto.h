#ifndef TEXTOVERPHOTO_H
#define TEXTOVERPHOTO_H

#include <QStyledItemDelegate>
#include <QApplication>

class TextOverPhoto : public QStyledItemDelegate{
    Q_OBJECT
    Q_DISABLE_COPY(TextOverPhoto)
public:
    explicit TextOverPhoto(QObject* parent = Q_NULLPTR)
        :QStyledItemDelegate(parent)
    {}
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE{
        QStyledItemDelegate::paint(painter,option,index);
        QVariant text = index.data(Qt::UserRole+2);
        if(text == "false") text = "";
        if(text.isValid()){
            const QStyle *style = option.widget ? option.widget->style() : QApplication::style();

            style->drawItemText(painter, option.rect, Qt::AlignCenter, option.palette, option.state & QStyle::State_Enabled, text.toString());
        }
    }
};

#endif // TEXTOVERPHOTO_H
