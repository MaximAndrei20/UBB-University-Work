class ValidatorException(Exception):
    def __init__(self, messageList):
        self._messageList = messageList

    def get_message(self):
        return self._messageList

    def __str__(self):
        result = ""
        for message in self.get_message():
            result += message
            result += "\n"
        return result
