#ifndef USERINFO_H
#define USERINFO_H

#include <QPoint>
#include <QScreen>
#include <QWidget>
#include <QMouseEvent>
#include "SetUp/SetUp.h"
#include <QStackedLayout>
#include "srcFile/USER.h"
#include "srcFile/TcpThread.h"
#include "uiFile/addinfo/AddInfo.h"
#include "modelFile/AiList_Model.h"
#include "uiFile/addinfo/AddVerify.h"
#include "modelFile/GroupList_Model.h"
#include "modelFile/FriendList_Model.h"

namespace Ui {
class UserInfo;
}

//用户界面类
class UserInfo : public QWidget
{
    Q_OBJECT

public:
    explicit UserInfo(QWidget *parent = nullptr);
    explicit UserInfo(TcpThread *thread, QWidget *parent = nullptr);
    ~UserInfo();
////------------------------------------界面模块函数-------------------------------------------------------------
public:
    //初始化添加的群聊界面
    int add_InitGroupInfoWidget(const QString &name, const QString &id, const QString headimg);
    //初始化好友界面
    int add_InitFriendInfoWidget(const QString &name, const QString &sign, const QString &number,
                                 const QString headimg,const QString &state);
public slots:
    //处理设置Ai结果
    int handle_SetAiResult(bool ok, const QString &ai_Name, const QString &ai_Sign,
                           const QString &ai_ApiKey, const QString &ai_ApiSecret);
    //处理获取Ai信息结果
    int handle_GetAiResult(bool ok,const QString &ai_Name,const QString &ai_Sign,
                           const QString &ai_ApiKey,const QString &ai_ApiSecret);
signals:
    //请求关闭线程
    void handle_TcpThreadClose(const QString& number);
////------------------------------------AI模块函数-------------------------------------------------------------
public slots:
    //请求服务器设置Ai信息
    int request_SetAiPackageAsJSON(const QString &type);
    //请求服务器获取Ai信息
    int request_GetAiPackageAsJSON(const QString &type);
////------------------------------------Tcp模块函数-------------------------------------------------------------
public:
    //初始化Tcp链接
    int init_userInfoTcpConnect();
////------------------------------------事件模块函数-------------------------------------------------------------
protected:
    //鼠标移动事件
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    //鼠标点击事件
    virtual void mousePressEvent(QMouseEvent *event) override;
    //鼠标释放事件
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    //事件过滤器
    virtual bool eventFilter(QObject *watched, QEvent *event) override;
////------------------------------------界面控件函数--------------------------------------------------------------
public:
    //初始化界面
    int init_UserInfoWidget();
public slots:
    //更新界面控件显示
    int new_UserInfoWidgetInfo();
private slots:
    //关闭界面函数
    void on_clos_Btn_clicked();
    //最小化界面函数
    void on_reduce_Btn_clicked();
    //设置
    void on_setup_Btn_clicked();
////------------------------------------添加好友(群组)模块函数-----------------------------------------------------
public slots:
    //处理新增好友链接结果操作
    int handle_AddFriendLinkResult(const QJsonObject &jsonObject);
    //将验证结果转发至TcpThread发送
    int relay_VerifyResultPackageAsJSON(const QJsonObject &jsondata);
    //获取添加的好友信息
    int request_AddFriendInfo(const QString &type, const QString &number);
    //处理请求好友验证操作
    int handle_ApplyForFriendVerify(const QString& type, const QString &number);
    //处理返回的好友信息结果
    void handle_ReturnFriendInfo(const QString& code, const QString& state, const QString &name,
                                 const QString &sex, const QString &sign, const QString &number,
                                 const QString &headimg_Path);
    //处理好友申请信息
    void handle_FriendApplyFor(const QString &name,const QString &sex, const QString &sign,
                               const QString &number,const QString &headimg_Path);
private slots:
    //添加好友或群组
    void on_addfriend_Btn_clicked();
signals:
    //转发至添加好友界面处理好友信息
    void relay_FriendInfoHandle(const QString& code, const QString& name,const QString& state,
                                const QString& sex, const QString &sign, const QString& number,
                                const QString& headimg_Path);

private:
    Ui::UserInfo *ui;
    bool ai_Ok;         //是否获取过Ai信息
    bool move_Ok;       //是否移动
    SetUp *Setup_GUI;   //设置窗口
    QPoint move_point;  //移动的距离
    AddInfo *Addfriend_GUI;      //添加好友或群组界面
    AddVerify *AddVerify_GUI;    //好友验证窗口
    TcpThread *tcpThread_Obj;    //数据处理线程
    QSharedPointer<AiList_Model> AiList;            //消息列表
    QSharedPointer<GroupList_Model> GroupList;      //群聊列表
    QSharedPointer<FriendList_Model> FriendList;    //好友列表
    QSharedPointer<QStackedLayout> Stacked_Layout;  //列表布局

};

#endif // USERINFO_H
