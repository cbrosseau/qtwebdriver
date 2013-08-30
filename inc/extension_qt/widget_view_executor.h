#ifndef WEBDRIVER_QT_WIDGET_VIEW_EXECUTOR_H_
#define WEBDRIVER_QT_WIDGET_VIEW_EXECUTOR_H_

#include "base/memory/scoped_ptr.h"
#include "extension_qt/q_view_executor.h"

#include <QtCore/QDebug>
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include <QtCore/QXmlStreamWriter>
#else
#include <QtXml/QXmlStreamWriter>
#endif

namespace webdriver {

class QWidgetViewVisualizerSourceCommand;

class QWidgetXmlSerializer {
public:
    typedef QHash<QString, QWidget*> XMLElementMap;

    QWidgetXmlSerializer(QIODevice* buff);

    void createXml(QWidget* widget);

    const XMLElementMap& getElementsMap() {
        return elementsMap_;
    }

    void setSession(Session* session) {
        session_ = session;
    }

    void setViewId(ViewId viewId) {
        viewId_ = viewId;
    }

    void setDumpAll(bool dumpAll) {
        dumpAll_ = dumpAll;
    }

    void setSupportedClasses(const QStringList& classes) {
        supportedClasses_ = classes;
    }

private:
    void addWidget(QWidget* widget);
    QString getElementName(const QObject* object) const;

    QXmlStreamWriter writer_;
    XMLElementMap elementsMap_;
    Session* session_;
    ViewId viewId_;
    bool dumpAll_;
    QStringList supportedClasses_;
};

class QWidgetViewCmdExecutorCreator : public ViewCmdExecutorCreator  {
public:
    static const ViewType WIDGET_VIEW_TYPE;
    
    QWidgetViewCmdExecutorCreator();
    virtual ~QWidgetViewCmdExecutorCreator(){}

    virtual ViewCmdExecutor* CreateExecutor(Session* session, ViewId viewId) const;
    virtual bool CanHandleView(Session* session, ViewId viewId, ViewType* viewType = NULL) const;
private:

    DISALLOW_COPY_AND_ASSIGN(QWidgetViewCmdExecutorCreator);
};	

/// QWebView based view's implementation
class QWidgetViewCmdExecutor : public QViewCmdExecutor {
public:
    explicit QWidgetViewCmdExecutor(Session* session, ViewId viewId);
    virtual ~QWidgetViewCmdExecutor();

    virtual void CanHandleUrl(const std::string& url, bool* can, Error **error);
    virtual void GoForward(Error** error) NOT_SUPPORTED_IMPL;
    virtual void GoBack(Error** error) NOT_SUPPORTED_IMPL;
    virtual void Reload(Error** error) NOT_SUPPORTED_IMPL;
    virtual void GetSource(std::string* source, Error** error);
    virtual void SendKeys(const ElementId& element, const string16& keys, Error** error);
    virtual void MouseDoubleClick(Error** error);
    virtual void MouseButtonUp(Error** error);
    virtual void MouseButtonDown(Error** error);
    virtual void MouseClick(MouseButton button, Error** error);
    virtual void MouseMove(const int x_offset, const int y_offset, Error** error);
    virtual void MouseMove(const ElementId& element, int x_offset, const int y_offset, Error** error);
    virtual void MouseMove(const ElementId& element, Error** error);
    virtual void ClickElement(const ElementId& element, Error** error);
    virtual void GetAttribute(const ElementId& element, const std::string& key, base::Value** value, Error** error);
    virtual void ClearElement(const ElementId& element, Error** error);
    virtual void IsElementDisplayed(const ElementId& element, bool ignore_opacity, bool* is_displayed, Error** error);
    virtual void IsElementEnabled(const ElementId& element, bool* is_enabled, Error** error);
    virtual void ElementEquals(const ElementId& element1, const ElementId& element2, bool* is_equal, Error** error);
    virtual void GetElementLocation(const ElementId& element, Point* location, Error** error);
    virtual void GetElementLocationInView(const ElementId& element, Point* location, Error** error);
    virtual void GetElementTagName(const ElementId& element, std::string* tag_name, Error** error);
    virtual void IsOptionElementSelected(const ElementId& element, bool* is_selected, Error** error);
    virtual void SetOptionElementSelected(const ElementId& element, bool selected, Error** error);
    virtual void GetElementSize(const ElementId& element, Size* size, Error** error);
    virtual void ElementSubmit(const ElementId& element, Error** error) NOT_SUPPORTED_IMPL;
    virtual void GetElementText(const ElementId& element, std::string* element_text, Error** error);
    virtual void GetElementCssProperty(const ElementId& element, const std::string& property, base::Value** value, Error** error) NOT_SUPPORTED_IMPL;
    virtual void FindElements(const ElementId& root_element, const std::string& locator, const std::string& query, std::vector<ElementId>* elements, Error** error);
    virtual void ActiveElement(ElementId* element, Error** error);
    virtual void SwitchToFrameWithNameOrId(const std::string& name_or_id, Error** error) NOT_SUPPORTED_IMPL;
    virtual void SwitchToFrameWithIndex(int index, Error** error) NOT_SUPPORTED_IMPL;
    virtual void SwitchToFrameWithElement(const ElementId& element, Error** error) NOT_SUPPORTED_IMPL;
    virtual void SwitchToTopFrame(Error** error) NOT_SUPPORTED_IMPL;
    virtual void SwitchToTopFrameIfCurrentFrameInvalid(Error** error) NOT_SUPPORTED_IMPL;
    virtual void NavigateToURL(const std::string& url, bool sync, Error** error);
    virtual void GetURL(std::string* url, Error** error);
    virtual void ExecuteScript(const std::string& script, const base::ListValue* const args, base::Value** value, Error** error) NOT_SUPPORTED_IMPL;
    virtual void ExecuteAsyncScript(const std::string& script, const base::ListValue* const args, base::Value** value, Error** error) NOT_SUPPORTED_IMPL;
    virtual void GetAppCacheStatus(int* status, Error** error) NOT_SUPPORTED_IMPL;
    virtual void GetCookies(const std::string& url, base::ListValue** cookies, Error** error) NOT_SUPPORTED_IMPL;
    virtual void SetCookie(const std::string& url, base::DictionaryValue* cookie_dict, Error** error) NOT_SUPPORTED_IMPL;
    virtual void DeleteCookie(const std::string& url, const std::string& cookie_name, Error** error) NOT_SUPPORTED_IMPL;
    virtual void GetStorageKeys(StorageType type, base::ListValue** keys, Error** error) NOT_SUPPORTED_IMPL;
    virtual void SetStorageItem(StorageType type, const std::string& key, const std::string& value, Error** error) NOT_SUPPORTED_IMPL;
    virtual void ClearStorage(StorageType type, Error** error) NOT_SUPPORTED_IMPL;
    virtual void GetStorageItem(StorageType type, const std::string& key, std::string* value, Error** error) NOT_SUPPORTED_IMPL;
    virtual void RemoveStorageItem(StorageType type, const std::string& key, std::string* value, Error** error) NOT_SUPPORTED_IMPL;
    virtual void GetStorageSize(StorageType type, int* size, Error** error) NOT_SUPPORTED_IMPL;
    virtual void GetGeoLocation(base::DictionaryValue** geolocation, Error** error) NOT_SUPPORTED_IMPL;
    virtual void SetGeoLocation(const base::DictionaryValue* geolocation, Error** error) NOT_SUPPORTED_IMPL;
    virtual void TouchClick(const ElementId& element, Error **error) NOT_SUPPORTED_IMPL;
    virtual void TouchDoubleClick(const ElementId& element, Error **error) NOT_SUPPORTED_IMPL;
    virtual void TouchDown(const int &x, const int &y, Error **error) NOT_SUPPORTED_IMPL;
    virtual void TouchUp(const int &x, const int &y, Error **error) NOT_SUPPORTED_IMPL;
    virtual void TouchMove(const int &x, const int &y, Error **error) NOT_SUPPORTED_IMPL;
    virtual void TouchLongClick(const ElementId& element, Error **error) NOT_SUPPORTED_IMPL;
    virtual void TouchScroll(const int &xoffset, const int &yoffset, Error **error) NOT_SUPPORTED_IMPL;
    virtual void TouchScroll(const ElementId &element, const int &xoffset, const int &yoffset, Error **error) NOT_SUPPORTED_IMPL;
    virtual void TouchFlick(const int &xSpeed, const int &ySpeed, Error **error) NOT_SUPPORTED_IMPL;
    virtual void TouchFlick(const ElementId &element, const int &xoffset, const int &yoffset, const int &speed, Error **error) NOT_SUPPORTED_IMPL;
    virtual void GetPlayerState(const ElementId& element, PlayerState*, Error**error);
    virtual void SetPlayerState(const ElementId& element, PlayerState, Error**error) NOT_SUPPORTED_IMPL;
    virtual void GetPlayerVolume(const ElementId& element, double*, Error**error) NOT_SUPPORTED_IMPL;
    virtual void SetPlayerVolume(const ElementId& element, double, Error**error) NOT_SUPPORTED_IMPL;
    virtual void GetPlayingPosition(const ElementId& element, double*, Error**error) NOT_SUPPORTED_IMPL;
    virtual void SetPlayingPosition(const ElementId& element, double, Error**error) NOT_SUPPORTED_IMPL;
    virtual void SetMute(const ElementId& element, bool, Error**error) NOT_SUPPORTED_IMPL;
    virtual void GetMute(const ElementId& element, bool*, Error**error) NOT_SUPPORTED_IMPL;
    virtual void VisualizerSource(std::string* source, Error** error);
    virtual void VisualizerShowPoint(Error** error) NOT_SUPPORTED_IMPL;

protected:
    typedef QHash<QString, QWidget*> XMLElementMap;    

    QWidget* getElement(const ElementId &element, Error** error);
    bool MatchNativeWidget(const QWidget* widget, const std::string& locator, const std::string& query);
    void FindNativeElementsByXpath(QWidget* parent, const std::string &query, std::vector<ElementId>* elements, Error **error);

private:
    scoped_ptr<QWidgetViewVisualizerSourceCommand> _visualizerSourceCommand;
    DISALLOW_COPY_AND_ASSIGN(QWidgetViewCmdExecutor);
};

}  // namespace webdriver

#endif  // WEBDRIVER_QT_WIDGET_VIEW_EXECUTOR_H_
