#include <sstream>
#include <cctype>
#include <cassert>
#include "csapp.h"
#include "message.h"
#include "connection.h"

Connection::Connection()
    : m_fd(-1), m_last_result(SUCCESS)
{
}

Connection::Connection(int fd)
    : m_fd(fd), m_last_result(SUCCESS)
{
  // TODO: call rio_readinitb to initialize the rio_t object
  rio_readinitb(&m_fdbuf, fd);
}

void Connection::connect(const std::string &hostname, int port)
{
  // TODO: call open_clientfd to connect to the server
  m_fd = open_clientfd(hostname.c_str(), std::to_string(port).c_str());
  // TODO: call rio_readinitb to initialize the rio_t object
  rio_readinitb(&m_fdbuf, m_fd);
}

Connection::~Connection()
{
  // TODO: close the socket if it is open
  close();
}

bool Connection::is_open() const
{
  // TODO
}

void Connection::close()
{
  Close(m_fd);
}

bool Connection::send(const Message &msg)
{
  // TODO: send a message
  // return true if successful, false if not
  // make sure that m_last_result is set appropriately
  if (msg.tag.length() + msg.data.length() + 2 > msg.MAX_LEN)
  {
    m_last_result = INVALID_MSG;
    return false;
  }
  if (rio_writen(m_fd, msg.tag.c_str(), msg.tag.length()) == -1 || rio_writen(m_fd, ":", 1) == -1 
  || rio_writen(m_fd, msg.data.c_str(), msg.data.length()) == -1 || rio_writen(m_fd, "\n", 1) == -1)
  {
    m_last_result = EOF_OR_ERROR;
    return false;
  }
  m_last_result = SUCCESS;
  return true;
}

bool Connection::receive(Message &msg)
{
  // TODO: send a message, storing its tag and data in msg
  // return true if successful, false if not
  // make sure that m_last_result is set appropriately
  char buf[255];
  ssize_t result = rio_readlineb(&m_fdbuf, buf, sizeof(buf));
  if(result == 0 || -1) {
    m_last_result = EOF_OR_ERROR;
    return false;
  }

  m_last_result = SUCCESS;
}
