# -*- coding: utf-8 -*-

# The U namespace contains a string builder in {U::Buffer} and a string
# representation in {U::String}.
module U
  load File.expand_path('../u/version.rb', __FILE__)
  require File.expand_path('../u/u', __FILE__)
  Version.load
end

# Ruby’s built-in String class.
class String
  # @return [U::String] A wrapper around the receiver that provides proper
  #   Unicode handling of its content
  # @note The receiver will receive #encode(Encoding::UTF_8)#freeze and you
  #   should thus probably not use the receiver after invoking #u on it.
  def u
    U::String.new(self)
  end
end
