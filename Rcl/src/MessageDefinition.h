#ifndef _MESSAGE_DEFINITION_H_
#define _MESSAGE_DEFINITION_H_

#include <QObject>

#include <rosidl_generator_c/message_type_support_struct.h>

class QTextStream;

class MessageData;
class MessageField;
class ServiceDefinition;

class MessageDefinition : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QList<QObject*> fields READ fieldsLO CONSTANT)
  friend class ServiceDefinition;
  MessageDefinition(QObject* _parent);
public:
  MessageDefinition(const QString& _type_name);
  ~MessageDefinition();
  static MessageDefinition* get(const QString& _type_name);
  bool isValid() const { return m_valid; }
  QString typeName() const { return m_type_name; }
  QVariantMap variantToMap(const QVariant& _list) const;
  QVariantMap deserializeMessage(const MessageData& _buffer) const;
  MessageData serializeMessage(const QVariantMap& _hash) const;
  quint32 serializedLength() const;
  const rosidl_message_type_support_t* typeSupport() const { return m_typesupport; }
  quint8* allocateZeroInitialised() const;
  void disallocate(const quint8* data) const;
private:
  void parseDefinition(const QString& _packagename, QTextStream& _definition);
private:
  QList<QObject*> fieldsLO() const;
private:
  QString m_type_name;
  bool m_valid = false;
  QList<MessageField*> m_fields;
  const rosidl_message_type_support_t* m_typesupport;
};

#endif
